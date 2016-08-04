//Author: Zane Draper
//With guidance from Professor Jefferson

"use strict";

//Global Variables
var API_KEY = "83NgjHJPbcCjCVLt";
var map;
var infowindow;
var markers = [];
var ids = [];
var curIndex;
var allBusinesses;
var city;
var type;
var directionsService;
var directionsDisplay;

//Function called onload
function init(){
	
	//Sets up on click methods
	document.querySelector("#search").onclick = getData;
	document.querySelector("#list").onclick = function(){
		zoomOnFirstResult();
		clearWindow();
		clearDirections();
		$("#right2").fadeOut("slow", function(){$("#right").fadeIn("fast")});
	};
	document.querySelector("#clear").onclick = function(){
		clearMarkers();
		
	};
	document.querySelector("#directions").onclick = enterAddress;
	
	//sets up the maps display
	var mapOptions = {
		center: {lat:39.828127, lng: -98.579404},
		zoom: 3
	};
	
	//checks for local storage of previous searches
	if(localStorage.getItem("ztd9457_location") != null){ 
		document.querySelector("#searchterm").value = localStorage.getItem("ztd9457_location");
	}
	if(localStorage.getItem("ztd9457_venue") != null) document.querySelector("#keyword").value = localStorage.getItem("ztd9457_venue");
		console.log(localStorage.getItem("ztd9457_location"));

	//sets up display for directions with google maps
	map = new google.maps.Map(document.getElementById('mapDiv'), mapOptions);
	directionsService = new google.maps.DirectionsService;
	directionsDisplay = new google.maps.DirectionsRenderer;
	
	directionsDisplay.setMap(map);
}

//PURPOSE: Drops down menu for navigation
function enterAddress(){
	$("#addressInput").slideDown("slow");
	
	document.querySelector("#directions").innerHTML = "Get Directions!";
	document.querySelector("#directions").onclick = showDirections;
}

//PURPOSE: Once address is inserted, allows for navigation display
function showDirections(){
	var state = document.querySelector("#state").value;
	var city2 = document.querySelector("#city").value;
	var street = document.querySelector("#street").value;
	
	state.trim();
	city2.trim();
	street.trim();
	
	//Checks to make sure there are values in the address
	if(street.length > 1) localStorage.setItem("ztd9457_street", document.querySelector("#street").value);
	if(state.length < 1) document.querySelector("#state").value = "Required Feild***";
	else if(city2.length < 1) document.querySelector("#city").value = "Required Feild***";
	else{
		
		localStorage.setItem("ztd9457_city", document.querySelector("#city").value);
		localStorage.setItem("ztd9457_state", document.querySelector("#state").value);
		
		setDirections(state, city2, street);
		
		document.querySelector("#directions").innerHTML = "Want Directions?";
		document.querySelector("#directions").onclick = enterAddress;
		
		$("#addressInput").slideUp("fast");
	}
}

//PURPOSE: get the data from the yelp server (calls to php)
function getData(){

	clearMarkers();
	clearBusinesses();

	city = document.querySelector("#searchterm").value;
	type = document.querySelector("#keyword").value;
	
	city = city.trim();
	type = type.trim();
	
	if(city.length < 1 || type.length < 1) return;
	
	document.querySelector("#dynamicContent").innerHTML = "<b>Searching " + city + " for " + type + "</b>";
	
	city = encodeURI(city); 
	type = encodeURI(type); 
			
	getYelpData(city, type);
}

//PURPOSE - contact php server for information
function getYelpData(city, type){		

	var message = {
		'action' : 'https://people.rit.edu/ztd9457/330/final/local.php',
		'method' : 'GET',
	};
	
	//requests info from php server
	$.ajax({
			'url' : message.action,
			'type' : 'GET',
			'success' : jsonLoaded,
			'data': { term : type, location : city},
			'error' : errorHandle,
	});
}

//PURPOSE: Once the information is loaded, this is called to display information
function jsonLoaded(obj){
	console.log("obj = " + obj + "\n\n");
	
	obj = JSON.parse(obj);
	
	if(obj.error){
		var status = obj.status;
		var description = obj.description;
		document.querySelector("#dynamicContent").innerHTML = "<h3><b>Error!</b></h3>" + "<p><i>" + status + "</i><p>" + "<p><i>" + description + "</i><p>";
		$("#dynamicContent").fadeIn(500);
		return; // Bail out
	}
	
	if(obj.businesses.length == 0){
		var status = "No results found";
		document.querySelector("#dynamicContent").innerHTML = "<p><i>" + status + "</i><p>" + "<p><i>";
		$("#dynamicContent").fadeIn(500);
		return; // Bail out
	}
	
	//cycles through the businesses
	allBusinesses = obj.businesses;
	console.log("allBusinesses.length = " + allBusinesses.length);
	var bigString = "<p><b>Here are " + allBusinesses.length + " businesses for " + type + " in " + city + "</b></p>";
	document.querySelector("#resultTitle").innerHTML = bigString;
	bigString = "";
	bigString += "<hr />";
	
	//creates windows for displaying info and populates the information
	for(var i = 0; i < allBusinesses.length; i++){
		var business = allBusinesses[i];
				
		bigString+= "<div class = 'category'>";
		
		if(business.image_url != null)
			bigString+="<img src='" + business.image_url + "'/>";
		else bigString+="<img src='images/null.png'/>";
			
		bigString+="<div class='details'>";
		
		if(business.name != null){
			bigString+="<h3>" + business.name + "</h3>";
			
			if(business.location.coordinate.latitude && business.location.coordinate.longitude){
				ids.push(business.id);
				addMarker(Number(business.location.coordinate.latitude), Number(business.location.coordinate.longitude), business.name + "<br/>" + business.location.city);
			}
		}
		else bigString+="<h3>No Business Title Available</h3>";
			
		if(business.location.neighborhoods == null){
			bigString+="<p><em>" + business.location.city + "</em></p>";
		}
		else bigString+="<p><em>" + business.location.neighborhoods[0] + ",  " + business.location.city + "</em></p>";
		
		if(business.rating_img_url != null)
			bigString+="<img src='" + business.rating_img_url_large + "'/>";
		
		bigString += "</div></div>";
	}
	
	zoomOnFirstResult();
	
	localStorage.setItem("ztd9457_location", city);
	localStorage.setItem("ztd9457_venue", type);
	
	console.log(localStorage.getItem("ztd9457_location"));
	
	document.querySelector("#dynamicContent").innerHTML = bigString;
	$("#dynamicContent").fadeIn(500);
}	

//PURPOSE: handle any errors
function errorHandle(){
	alert("Looks like your search was invalid! Try again!");
	document.querySelector("#dynamicContent").innerHTML = "No Results";
}

//PURPOSE: this displays the directions for the google maps navigation
function setDirections(state, city2, street){
	directionsDisplay.setMap(map);
	
	var address =street + " " + city2 + " " + state;
	
	//shows the navigation of the maps
	directionsService.route({
		origin: address,
		destination: allBusinesses[curIndex].location.display_address[0] + " " + allBusinesses[curIndex].location.display_address[1] + " " + allBusinesses[curIndex].location.display_address[2],
		travelMode: google.maps.TravelMode.DRIVING
	}, 
	function(response, status) {
		if (status === google.maps.DirectionsStatus.OK) {
		  directionsDisplay.setDirections(response);
		} else {
		  window.alert('Directions request failed due to ' + status);
		}
	});
}

//this retrieves information on a particular business
function getBusinessInfo(index){
	console.log(ids[index] + "\n");
	
	var id = "" + ids[index];
	
	curIndex = index;
	
	var business = allBusinesses[index];
	
	//inserts business info into the display
	document.querySelector("#localName").innerHTML = business.name;
	document.querySelector("#localPhone").innerHTML = business.phone;
	document.querySelector("#localAddress").innerHTML = business.location.display_address[0] + "\n" + business.location.display_address[1] + "\n" +business.location.display_address[2];
	document.querySelector("#localSnippetRating").src = business.rating_img_url_large;
	document.querySelector("#localSnippet").innerHTML = business.snippet_text;
	document.querySelector("#localSnippetImg").src = business.snippet_image_url;
	document.querySelector("#localRating").innerHTML = business.rating;
	document.querySelector("#titleLink").href = business.url;
	
	var html = "";
	
	for(var i = 0; i < business.categories.length; i++){
		var cat = business.categories[i];
		html += "<p>" + cat[0] + "</p>";
	}
	
	document.querySelector("#cats").innerHTML = html;
	
	$("#right").fadeOut("slow", function(){$("#right2").fadeIn("fast")});
}

//PURPOSE: places a marker on the map
function addMarker (latitude, longitude, title){
	
	var position = {lat:latitude, lng: longitude};
	var marker = new google.maps.Marker({position:position, map:map});
	marker.setTitle(title);
	
	google.maps.event.addListener(marker, 'click', function(e){
		getBusinessInfo(markers.indexOf(this));
		makeInfoWindow(this.position, this.title);
		//setDirections(this.position);
	});
	
	markers.push(marker);
}

//PURPOSE: places a info window on a clicked marker
function makeInfoWindow(position, msg){
	if(infowindow) infowindow.close();
	
	infowindow = new google.maps.InfoWindow({
		map:map,
		position:position,
		content: "<b>" + msg + "</b>"
	});
	
	map.panTo(position);
	map.setZoom(20);
	
	clearDirections();
	
}

//PURPOSE: methods for clearing the map
function clearMarkers(){
	clearWindow();
	for(var i = 0; i < markers.length; i++){
		markers[i].setMap(null);
	}
	markers=[];
	ids = [];
	
	clearDirections();
}
function clearWindow(){
	if(infowindow) infowindow.close();
}
function clearDirections(){
	directionsDisplay.setMap(null);
}
function zoomOnFirstResult(){
	if(markers.length == 0) return;
	map.panTo(markers[0].position);
	map.setZoom(14);
}
function clearBusinesses(){
	allBusinesses = [];
}