
var ws = new WebSocket('ws://' + location.host);

ws.onopen = function(ev)  { console.log(ev); };
ws.onerror = function(ev) { console.log(ev); };
ws.onclose = function(ev) { console.log(ev); };
ws.onmessage = function(ev) { console.log(ev); };

ws.send(JSON.stringify({"action" : "registerUser", "username" : "Randy"}));
