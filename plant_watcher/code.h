#ifndef SERVER_CODE_H
#define SERVER_CODE_H

#include <ESP8266WebServer.h>

const char htmlContent[] = R"====(
<!DOCTYPE html>
<html>
<head>
  <title>Omotools IoT WebViewer</title>
  <style>
    body {
      text-align: center;
      margin: 0;
      font-family: Arial, sans-serif;
      background-color: #f0f0f0; /* Keep the background color unchanged */
    }

    #main-header {
      display: flex;
      align-items: center;
      background-color: #115690;
      color: white;
      padding: 10px;
    }

    #logo {
      align-items: center;
      margin-right: 10px;
      max-height: 50px;
    }

    .controllers {
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      margin-top: 20px;
    }

    .controller-box {
      border: 2px solid #99458b;
      padding: 10px;
      margin: 10px;
      width: 500px; /* Adjust the width as needed */
      text-align: center;
    }

    .button {
      background-color: #f47332;
      border: 1px;
      color: white;
      padding: 15px 32px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 16px;
      margin: 4px 2px;
      cursor: pointer;
      border-radius: 8px;
      width: 100%; /* Make buttons fill the width of the container */
    }

    h2 {
      color: #dc946f; /* Adjust the color as needed */
    }

    table {
      width: 100%;
    }

    table, th, td {
      border: 0px solid #dc946f;
      border-collapse: collapse;
    }

    th, td {
      padding: 15px;
      text-align: center;
    }

    .soil-box {
      border: 2px solid #333; 
      padding: 20px; 
      margin-top: 20px; 
      max-width: 400px; 
      position: relative;
    }

    .soil-img {
      position: absolute; 
      right: 0; 
      top: 0; 
      width: 40%; 
      height: 100%; 
    }
  </style>
</head>
<body>
  <div id="main-header">
    <img id="logo" src="https://onmyowntechnology.com/images/omotec_logo.png" alt="Omotools Logo">
    <h1>Omotools IoT WebViewer</h1>
  </div>

    <div class="controller-box soil-box" style="color: {statusColor};">
      <h2>Soil Moisture</h2>
      <p>Value: {soilValue}</p>
      <p>Status: {statusMessage}</p>
      <img src="{gifURL}" alt="Soil Moisture Status" class="soil-img">
    </div>
  </div>

  <script>
    function turnOn() { fetch('/on'); }
    function turnOff() { fetch('/off'); }
    setTimeout(function(){ location.reload(); }, 1000);
  </script>
</body>
</html>
)====";

#endif
