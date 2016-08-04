//The slider UI was derived from BrennaOBrian's tutorial at brennaobrian.com. The colors were changed to match our UI
// An IIFE ("Iffy") - see the notes in mycourses
(function(){
	"use strict";
	
	//Variables
	var NUM_SAMPLES = 256;
	var SOUND_1 = 'media/Control.mp3';
	var SOUND_2 = 'media/Hold Me Down.mp3';
	var audioElement;
	var analyserNode;
	var canvas,ctx;
	var sliderValue=0.5;
	var maxRadius = 100;
	var radiusMult = 1;
	var maxStroke = 5;
	var invert = false;
	var noise = false;
	var colorPick = false;
	var opacity = 0;
	var colorNum = 0.2;
	var frequency = true;
	var gradient = false;
	var grd;
	
	var audioBlob1 = {x: 210, y:-10};
	var blobArray = [audioBlob1];
	
	var mouse = {};
	var points = new Array(0);
	var shapeType = 1;
	
	var tempStrokeStyle = "red";
	var tempFillStyle = "red";
	
	var topCanvas, topCtx;
	var tint = "off";
	
	//Initalize everything
	function init(){
		// set up canvas stuff
		canvas = document.querySelector('#mainCanvas');
		ctx = canvas.getContext("2d");
		var height = window.innerHeight;
		
		topCanvas = document.querySelector('#topCanvas');
		topCtx = topCanvas.getContext("2d");
		topCtx.strokeStyle = ctx.strokeStyle;
		topCtx.fillStyle = ctx.fillStyle ;
		
		canvas.width = window.innerWidth - 350;
		canvas.height = window.innerHeight;
		topCanvas.width = window.innerWidth - 350;
		topCanvas.height = window.innerHeight;
		
		document.getElementById('controls').setAttribute('class','wide');
		document.getElementById('controls').style.height = height + "px";
		
		// get reference to <audio> element on page
		audioElement = document.querySelector('audio');
		
		// call our helper function and get an analyser node
		analyserNode = createWebAudioContextWithAnalyserNode(audioElement);
		
		// get sound track <select> and Full Screen button working
		setupUI();
		
		// load and play default sound into audio element
		playStream(audioElement,SOUND_1);
		
		// start animation loop
		update();
		
		canvas.onmousedown = drawShape;
	}
	
	//For clearing the gradients
	function clearTopCanvas(){
		topCtx.clearRect(0, 0, topCtx.canvas.width, topCtx.canvas.height);
	}
	
	//Given By Proffessor
	function createWebAudioContextWithAnalyserNode(audioElement) {
		var audioCtx, analyserNode, sourceNode;
		
		audioCtx = new (window.AudioContext || window.webkitAudioContext);
		
		analyserNode = audioCtx.createAnalyser();
		
		analyserNode.fftSize = NUM_SAMPLES;
		
		sourceNode = audioCtx.createMediaElementSource(audioElement); 
		sourceNode.connect(analyserNode);
		
		analyserNode.connect(audioCtx.destination);
		return analyserNode;
	}
	
	//Connects functions with UI elements
	function setupUI(){
		document.querySelector("#trackSelect").onchange = function(e){
		
			playStream(audioElement,e.target.value);
		};
		
		document.querySelector("#gradientSelect").onchange = function(e){
		
			tint = e.target.value;
		};

		document.querySelector("#fsButton").onclick = function(){
		
			requestFullscreen(canvas);
		};

		document.querySelector("#clearButton").onclick = function(){
		
			points = new Array(0);
		};
		
		
		document.querySelector("#slider1").onchange = function(e){
			
			radiusMult = e.target.value;
		};
		
		document.querySelector("#slider2").onchange = function(e){
			
			opacity = 250 * e.target.value;
		};
		
		document.querySelector("#colorPicker").onchange = function(e){
		
			colorNum = e.target.value;
		};
		
		document.getElementById('invertCheck').onchange = function(e){
			if(invert == false)
				invert = true;
			else invert = false;
		};
		
		document.getElementById('waveformCheck').onchange = function(e){
			if(frequency == false)
				frequency = true;
			else frequency = false;
		};
		
		document.getElementById('noiseCheck').onchange = function(e){
			if(noise == false)
				noise = true;
			else noise = false;
		};
					
		document.querySelector('#clearGrad').onclick = function(e){
			gradient = false;
			console.log(gradient);
		}
		
		document.getElementById('randGrad').onmouseover = function(e){
			document.getElementById('randGrad').style.background= "-moz-radial-gradient(purple, navy, darkgreen)";
			document.getElementById('randGrad').style.background= "-webkit-radial-gradient(purple, navy, darkgreen)";
			document.getElementById('randGrad').style.background= "radial-gradient(purple, navy, darkgreen)";
		}
		document.getElementById('randGrad').onmouseout = function(e){
			document.getElementById('randGrad').style.background= "black";
		}
		
		//stroke rectangle button
		document.getElementById('strokeRectCheck').onclick = function(e){
				shapeType = 2;
		};
		document.getElementById('strokeRectCheck').onmouseover = function(e){
			document.getElementById('strokeRectCheck').style.borderRadius = "2px";
			document.getElementById('strokeRectCheck').style.borderColor= "#178169";
		}
		document.getElementById('strokeRectCheck').onmouseout = function(e){
			document.getElementById('strokeRectCheck').style.borderRadius = "12px";
			document.getElementById('strokeRectCheck').style.borderColor= "#093a2f";
			}
		
		//fill rectangle button
		document.getElementById('fillRectCheck').onclick = function(e){
				shapeType = 3;
		};
		document.getElementById('fillRectCheck').onmouseover = function(e){
			document.getElementById('fillRectCheck').style.borderRadius = "2px";
			document.getElementById('fillRectCheck').style.backgroundColor= "#178169";
			document.getElementById('fillRectCheck').style.borderColor= "black";				
		}
		document.getElementById('fillRectCheck').onmouseout = function(e){
			document.getElementById('fillRectCheck').style.borderRadius = "12px";
			document.getElementById('fillRectCheck').style.backgroundColor= "black";
			document.getElementById('fillRectCheck').style.borderColor= "#093a2f";
		}
		
		//stroke circle button
		document.getElementById('strokeCircleCheck').onclick = function(e){
				shapeType = 1;
		};
		document.getElementById('strokeCircleCheck').onmouseover = function(e){
			document.getElementById('strokeCircleCheck').style.borderRadius = "50%";
			document.getElementById('strokeCircleCheck').style.borderColor= "#178169";
		}
		document.getElementById('strokeCircleCheck').onmouseout = function(e){
			document.getElementById('strokeCircleCheck').style.borderRadius = "12px";
			document.getElementById('strokeCircleCheck').style.borderColor= "#093a2f";
		}
		
		//fill circle button
		document.getElementById('fillCircleCheck').onclick = function(e){
				shapeType = 4;
		};
		document.getElementById('fillCircleCheck').onmouseover = function(e){
			document.getElementById('fillCircleCheck').style.borderRadius = "50%";
			document.getElementById('fillCircleCheck').style.backgroundColor= "#178169";
			document.getElementById('fillCircleCheck').style.borderColor= "black";
		}
		document.getElementById('fillCircleCheck').onmouseout = function(e){
			document.getElementById('fillCircleCheck').style.borderRadius = "12px";
			document.getElementById('fillCircleCheck').style.backgroundColor= "black";
			document.getElementById('fillCircleCheck').style.borderColor= "#093a2f";
		}
		//random gradient button and its clear
		document.querySelector('#randGrad').onclick = function(e){
						
			gradient = true;
			console.log(gradient);
		
			grd = ctx.createRadialGradient(window.innerWidth/2,window.innerHeight/2,window.innerWidth/2,window.innerWidth/2,window.innerHeight/2,0);
			var a = Math.floor(Math.random()*255);
			var b = Math.floor(Math.random()*255);
			var c = Math.floor(Math.random()*255);
			var d = Math.floor(Math.random()*255);
			var e = Math.floor(Math.random()*255);
			var f = Math.floor(Math.random()*255);
			grd.addColorStop(0,"rgba("+a+","+b+","+c+",0.8)");
			grd.addColorStop(1,"rgba("+d+","+e+","+f+",0.7)");
		}
		document.getElementById('randGrad').onmouseover = function(e){
			document.getElementById('randGrad').style.background= "-moz-radial-gradient(purple, navy, darkgreen)";
		}
		document.getElementById('randGrad').onmouseout = function(e){
			document.getElementById('randGrad').style.background= "black";

		}
		
		//Color Picker
		//check box
		document.getElementById('colorPickCheck').onchange = function(e){
			if(colorPick == false)
				colorPick = true;
			else colorPick = false;
		};
		
		//slider
		document.getElementById('colorPicker').style.background = "-moz-linear-gradient(left,red,orange,yellow,green,blue,indigo,violet)";
		document.getElementById('colorPicker').style.background = "-webkit-linear-gradient(left,red,orange,yellow,green,blue,indigo,violet)";
		document.getElementById('colorPicker').style.background = "-webkit-gradient(left,red,orange,yellow,green,blue,indigo,violet)";
		document.getElementById('colorPicker').style.background = "linear-gradient(left,red,orange,yellow,green,blue,indigo,violet)";
		document.getElementById('colorPicker').style.background = "-ms-gradient(left,red,orange,yellow,green,blue,indigo,violet)";
		
	}
	
	//By Proffessor
	function playStream(audioElement,path){
		audioElement.src = path;
		audioElement.play();
		audioElement.volume = 0.2;
		document.querySelector('#status').innerHTML = "Now playing: " + path;
	}
	
	//Updates the image every frame
	function update() { 
		// this schedules a call to the update() method in 1/60 seconds
		setTimeout( this, 100 );
		requestAnimationFrame(update);
		
		/*
			Nyquist Theorem
			http://whatis.techtarget.com/definition/Nyquist-Theorem
			The array of data we get back is 1/2 the size of the sample rate 
		*/
		
		// create a new array of 8-bit integers (0-255)
		var data = new Uint8Array(NUM_SAMPLES/2); 
		
		// populate the array with the frequency data
		// notice these arrays can be passed "by reference" 
		
		if(frequency == true)
			analyserNode.getByteFrequencyData(data);
		else
			analyserNode.getByteTimeDomainData(data); // waveform data
		
		// DRAW!
		ctx.clearRect(0,0, canvas.width, canvas.height);  
		var barWidth = 4;
		var barSpacing = 1;
		var barHeight = 4;
		var topSpacing = 420;
		
		if(colorPick == true){
		
			console.log(colorNum);
			
			if(colorNum == 0.2){
					tempStrokeStyle = "red";
					tempFillStyle = "red";
			}
			
			else if(colorNum == 0.3){
					tempStrokeStyle = "orange";
					tempFillStyle = "orange";
			}
			
			else if(colorNum == 0.4){
					tempStrokeStyle = "yellow";
					tempFillStyle = "yellow";
			}
			
			else if(colorNum == 0.5){
					tempStrokeStyle = "green";
					tempFillStyle = "green";
			}
			
			else if(colorNum == 0.6){
					tempStrokeStyle = "blue";
					tempFillStyle = "blue";
			}
			
			else if(colorNum == 0.7){
					tempStrokeStyle = "indigo";
					tempFillStyle = "indigo";
			}
			
			else if(colorNum == 0.8){
					tempStrokeStyle = "violet";
					tempFillStyle = "violet";
			}	
		
		}
			
		for(var k = 0; k < points.length; k++){
		
		
			var percent = data[points[k].dp] / 255;
			var circleRadius = percent * points[k].r;
			
			if(points[k].type == 1){
				ctx.beginPath();
				ctx.lineWidth = maxStroke * percent;
				if(colorPick == true)
					ctx.strokeStyle = tempStrokeStyle;
				else if(gradient == true)
					ctx.strokeStyle = grd;
				else 
					ctx.strokeStyle = makeColor(points[k].re,points[k].g,points[k].b, .34 - percent/3.0);
				ctx.arc(points[k].x, points[k].y, circleRadius/5 * radiusMult, 0, 2 * Math.PI, false);
				ctx.stroke();
				ctx.closePath();
			}
			else if(points[k].type == 4){
				ctx.beginPath();
				ctx.lineWidth = maxStroke * percent;
				if(colorPick == true)
					ctx.fillStyle = tempFillStyle;
				else if(gradient == true)
					ctx.fillStyle = grd;
				else
					ctx.fillStyle = makeColor(points[k].re,points[k].g,points[k].b, .34 - percent/3.0);
				ctx.arc(points[k].x, points[k].y, circleRadius/2 * radiusMult, 0, 2 * Math.PI, false);
				ctx.fill();
				ctx.closePath();
			}
			else if(points[k].type == 3){
				if(colorPick == true)
					ctx.fillStyle = tempFillStyle;
				else if(gradient == true)
					ctx.fillStyle = grd;
				else 
					ctx.fillStyle = makeColor(points[k].re,points[k].g,points[k].b, .34 - percent/3.0);
				ctx.fillRect(points[k].x - circleRadius/2 * radiusMult, points[k].y - circleRadius/2 * radiusMult,circleRadius * radiusMult,circleRadius * radiusMult);
				ctx.fill();
			}
			else if(points[k].type == 2){
				if(colorPick == true)
					ctx.strokeStyle = tempStrokeStyle;
				else if(gradient == true)
					ctx.strokeStyle = grd;
				else 
					ctx.strokeStyle = makeColor(points[k].re,points[k].g,points[k].b, .34 - percent/3.0);
				ctx.strokeRect(points[k].x - circleRadius/2 * radiusMult, points[k].y - circleRadius/2 * radiusMult,circleRadius * radiusMult,circleRadius * radiusMult);
				ctx.stroke();
			}
			
			
			ctx.beginPath();
		}
		
		// loop through the data and draw!
		for(var i=0; i<data.length - 12; i++) { 
			ctx.fillStyle = 'rgba(0,255,0,0.6)'; 
			
			// the higher the amplitude of the sample (bin) the taller the bar
			// remember we have to draw our bars left-to-right and top-down
			//ctx.fillRect(i * (barWidth + barSpacing),topSpacing + 256-data[i],barWidth,barHeight); 
			for( var j = 0; j < 1; j += 8){
				ctx.fillRect(640 - i * 2 * (barWidth + barSpacing),(canvas.height - 100 + j) - data[i] - 20,barWidth,barHeight);
				ctx.fillRect(640 + i * 2 * (barWidth + barSpacing),(canvas.height - 100 + j) - data[i] - 20,barWidth,barHeight);
			}
			
			/*ctx.beginPath();
			ctx.fillStyle = makeColor(0, 0, 255, .10 - percent/10.0);
			ctx.arc(canvas.width/2, canvas.height/2, circleRadius * 1.5, 0, 2 * Math.PI, false);
			ctx.fill();
			ctx.closePath();
			
			ctx.save();
			ctx.beginPath();
			ctx.fillStyle = makeColor(200, 200, 0, .50 - percent/5.0);
			ctx.arc(canvas.width/2, canvas.height/2, circleRadius * .50, 0, 2 * Math.PI, false);
			ctx.fill();
			ctx.closePath();*/
			
			ctx.restore();
			
			var percent = data[i] / 220;
			var circleRadius = percent * maxRadius;
			ctx.beginPath();
			
			
		}
		manipulatePixels();
	} 
	
	
	function manipulatePixels(){
		var imageData = ctx.getImageData(0,0, canvas.width, canvas.height);
		
		var data = imageData.data;
		var length = data.length;
		var width = imageData.width;
		
		for(var i = 0; i < length; i+= 8){
			if(tint != "off"){
				if(tint == "red")
					data[i] = data[i] + 100;
				else if(tint == "green")
					data[i+1] = data[i+1] + 100;
				else if(tint == "blue")
					data[i+2] = data[i+2] + 100;
			}
			if(invert){
				var red = data[i], green = data[i + 1], blue = data[i + 2];
				data[i] = 255 - red;
				data[i+1] = 255 - green;
				data[i + 2] = 255 - blue;
			}
			if( noise && Math.random() < .050){
				//data[i] = data[i + 1] = data[i+2] = 128; //gray noise
				//data[i] = data[i + 1] = data[i+2] = 255; //white noise
				data[i] = data[i + 1] = data[i+2] = 0; //black noise
				data[i+3] = 255; //alpha
			}
			
			data[i + 3] = 250 - opacity;
			
		}
		
		ctx.putImageData(imageData, 0, 0);
	}
	
	
	function audioBlobAdder(){
		var audioBlobNext = {x: Math.floor((Math.random() * 640) + 1), y:-10};
		blobArray = [audioBlobNext];
	}
	
	// HELPER
	function makeColor(red, green, blue, alpha){
		var color='rgba('+red+','+green+','+blue+', '+alpha+')';
		return color;
	}
	
	 // FULL SCREEN MODE
	function requestFullscreen(element) {
		if (element.requestFullscreen) {
		  element.requestFullscreen();
		} else if (element.mozRequestFullscreen) {
		  element.mozRequestFullscreen();
		} else if (element.mozRequestFullScreen) { // camel-cased 'S' was changed to 's' in spec
		  element.mozRequestFullScreen();
		} else if (element.webkitRequestFullscreen) {
		  element.webkitRequestFullscreen();
		}
		// .. and do nothing if the method is not supported
	};
	
	function drawShape(e){
		getMouse(e);
		
		var point = {x: mouse.x, y:mouse.y, dp: (Math.floor(Math.random() * (100 - 10)) + 10), r: (Math.floor(Math.random() * (300 - 100)) + 150), type: shapeType, re: (Math.floor(Math.random() * (255 - 0)) + 0), g: (Math.floor(Math.random() * (255 - 0)) + 0), b: (Math.floor(Math.random() * (255 - 0)) + 0)};
		points.push(point);
		var len = points.length;
		console.log(points[len - 1].x + ' ' + points[len - 1].y + ' ' + points[len - 1].r + ' ' + points[len - 1].dp);
	}
	
	function getMouse(e){
		mouse.x = e.pageX - e.target.offsetLeft;
		mouse.y = e.pageY - e.target.offsetTop;
	}
	
	
	window.addEventListener("load",init);
}());
	