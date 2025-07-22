<!DOCTYPE html>
<html>
<head>
  <title>BRAVAN Lighting Dashboard</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body {
      font-family: Arial, sans-serif;
      background-color: #f7f9fc;
      text-align: center;
      padding: 50px;
    }
    h1 {
      color: #333;
    }
    .button {
      padding: 15px 30px;
      margin: 20px;
      font-size: 18px;
      border: none;
      border-radius: 10px;
      cursor: pointer;
      transition: background-color 0.3s;
    }
    .on {
      background-color: #4CAF50;
      color: white;
    }
    .on:hover {
      background-color: #45a049;
    }
    .off {
      background-color: #f44336;
      color: white;
    }
    .off:hover {
      background-color: #da190b;
    }
    #status {
      font-size: 20px;
      margin-top: 20px;
      color: #555;
    }
  </style>
</head>
<body>

  <h1>Wi-Fi Lighting Control</h1>

  <button class="button on" onclick="sendCommand('on')">Turn ON</button>
  <button class="button off" onclick="sendCommand('off')">Turn OFF</button>

  <div id="status">Status: Unknown</div>

  <script>
    function sendCommand(action) {
      fetch('/' + action)
        .then(response => response.text())
        .then(data => {
          document.getElementById("status").innerText = "Status: " + data;
        })
        .catch(error => {
          console.error("Error:", error);
          document.getElementById("status").innerText = "Status: Error";
        });
    }
  </script>

</body>
</html>
