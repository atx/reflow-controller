/*
 *  Copyright (C) Josef Gajdusek <atx@atx.name>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

PRESET_PROFILES = [
{
	name: "Reflow",
	profile: "0 25\n" +
			 "120 130\n" +
			 "210 130\n" +
			 "300 200\n" +
			 "400 25"
},{
	name: "Hold-150",
	profile:
		"0 0\n" +
		"100 150\n" +
		"500 150\n" +
		"600 0"
},{
	name: "Hold-200",
	profile:
		"0 0\n" +
		"100 200\n" +
		"500 200\n" +
		"600 0"
}]

$.fn.extend({
	disable: function() {
		this.each(function() {
			$(this).attr("disabled", "disabled")
		})
	},
	enable: function() {
		this.each(function() {
			$(this).removeAttr("disabled")
		})
	}
})

// Kind of hackish fix to prevent flooding of the device, set when we are waiting for /status
var waiting_flag = false

var identity = function(i) { return i }

STATUS_SETTINGS =
{
	"temp_board":
	{
		name: "Board temperature",
		transform: function(i) { return (i / 1000).toFixed(1) + " &degC" }
	},
	"temp_oven":
	{
		name: "Oven temperature",
		transform: function(i) { return (i / 1000).toFixed(1) + " &degC"}
	},
	"oven_time":
	{
		name: "Profile time",
		transform: identity
	}
}

// This will map status keys to elements
status_map = {}

profile = []
temperature = []

ovenRunning = false

var pollOven = function(d) {
	if (waiting_flag)
		return
	waiting_flag = true
	$.getJSON("/status", function(d) {
		for (var key in d) {
			if (!status_map[key])
				continue
			status_map[key].html(STATUS_SETTINGS[key].transform(d[key]))
		}

		if (ovenRunning != d.is_running) {
			onOvenChangedState(d.is_running)
		}

		// Add temperature point
		if (d.is_running) {
			temperature.push({time: d.oven_time, temperature: d.temp_oven / 1000})
			updateGraph();
		}

	}).always(function() {
		waiting_flag = false
	})
}

var loadProfileFromOven = function() {
	$.get("/profile", function(d) {
		$("#profile-input").val(d)
		onProfileInputChange()
	})
}

var profileTemp = function(d) { return d.temp }
var profileTime = function(d) { return d.time }

var temperatureValue = function(d) { return d.temperature }
var temperatureTime = function(d) { return d.time }

var updateGraph = function() {
	var svg = d3.select("#chart")

	var xScale = d3.scale.linear()
					.domain([0, d3.max(profile, profileTime)])
					.range([0, $("#chart").width()])

	var yScale = d3.scale.linear()
					.domain([0, Math.max(d3.max(profile, profileTemp),
										 d3.max(temperature, temperatureValue) || 0)])
					.range([$("#chart").height(), 0])

	var xAxis = d3.svg.axis()
					.scale(xScale)
					.orient("bottom")
	var yAxis = d3.svg.axis()
					.scale(yScale)
					.orient("left")

	d3.select("#timeaxis").transition().call(xAxis)
	d3.select("#tempaxis").transition().call(yAxis)

	d3.select("#profilepath")
			.datum(profile)
			.transition()
			.attr("d", d3.svg.line()
						.x(function(d) { return xScale(profileTime(d)) })
						.y(function(d) { return yScale(profileTemp(d)) }))

	d3.select("#datapath")
			.datum(temperature)
			.transition()
			.attr("d", d3.svg.line()
						.x(function(d) { return xScale(temperatureTime(d)) })
						.y(function(d) { return yScale(temperatureValue(d)) }))
}

var parseProfile = function(str) {
	var arr = str.trim().split("\n")
	var res = []
	for (var i = 0; i < arr.length; i++) {
		var sub = arr[i].split(" ")
		if (sub.length != 2)
			return null
		var ele = {
			time: parseInt(sub[0]),
			temp: parseInt(sub[1]),
		}
		if (isNaN(ele.time) ||
				isNaN(ele.temp) ||
				(res.length > 0 && res[res.length - 1].time >= ele.time))
			return null
		res.push(ele)
	}
	return res
}

var stringifyProfile = function(prf) {
	var res = ""
	for (var i = 0; i < prf.length; i++)
		res += prf[i].time + " " + prf[i].temp + "\n"
	return res
}

var onProfileInputChange = function() {
	var self = $("#profile-input")
	var nprf = parseProfile(self.val())

	if (nprf == null) {
		self.css("border-color", "red")
	}
	else {
		self.css("border-color", "")
		profile = nprf
		temperature = []
		updateGraph()
	}
}

var onOvenChangedState = function(run) {
	ovenRunning = run;
	if (run) {
		$("#button-start")
			.addClass("btn-danger")
			.removeClass("btn-success")
			.text("Stop")
			.enable()
		$(".preset-button, #profile-input").attr("disabled", "disabled")
		temperature = []
		// Maybe someone else loaded the profile
		// This also takes care of the graph updating to clear the temperature
		loadProfileFromOven()
	}
	else {
		$("#button-start")
			.removeClass("btn-danger")
			.addClass("btn-success")
			.text("Start")
			.enable()
		$(".preset-button, #profile-input").removeAttr("disabled")
	}
}

var ovenStart = function() {
	$.post("/profile", stringifyProfile(profile))
	$.post("/start")
}

var ovenStop = function() {
	$.post("/stop")
}

$("document").ready(function() {
	loadProfileFromOven()

	// Initialize the profile input

	$("#profile-input").bind("input propertychange", onProfileInputChange)

	PRESET_PROFILES.forEach(function (e, i) {
		$("#wrap-profile").append(
			"<button type=\"button\" class=\"btn btn-info preset-button\">" +
			e.name + "</button>")
			.children().last().bind("click", function(ev) {
				$("#profile-input").val(e.profile)
				onProfileInputChange();
			})
	})

	$("#button-start").click(function() {
		$(this).disable()
		if (!ovenRunning)
			ovenStart()
		else
			ovenStop()
	})

	// Initialize the status table
	for (var key in STATUS_SETTINGS) {
		status_map[key] = $(
					"<tr>" +
						"<td class=\"field-name\">" + STATUS_SETTINGS[key].name + "</td>" +
						"<td class=\"field-value\">...</td>" +
					"</tr>").appendTo("#status").children().last()
	}

	// Initialize the graph
	var svg = d3.select("#wrap-chart")
			.append("svg")
				.attr("id", "chart")
				.attr("width", "100%")
				.attr("height", "100%")

	svg.append("g")
		.attr("id", "timeaxis")
		.attr("class", "axis axis-x")
		.attr("transform", "translate(0, " + $("#chart").height() + ")")

	svg.append("g")
		.attr("id", "tempaxis")
		.attr("class", "axis axis-y")

	svg.append("path")
		.attr("id", "datapath")
		.attr("class", "path")
		.datum(temperature)

	svg.append("path")
		.attr("id", "profilepath")
		.attr("class", "path path-limit")
		.datum(profile)

	// Poll the oven every second
	setInterval(pollOven, 1000)
})
