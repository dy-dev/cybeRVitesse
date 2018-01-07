var config = {
    //relayURL: "ws://10.0.0.10:1234 ",
    relayURL: "ws://192.168.0.50:1234 ",
    //relayURL: "ws://localhost:1234",
    remoteHost: "www.google.com",
    remotePort: 80
};

function RelayClient(config, msg, handler) {
    $('#div1').text(config.relayURL);
    var connected = false;
    var connectHandler = handler;
    var socket = new WebSocket(config.relayURL);
    
    socket.onopen = function () {
        socket.send(JSON.stringify(msg));
    };
    socket.onmessage = function (event) {
        $('#div1').text(event.data);
        if (!connected && event.data == 'connected') {
            $('#div2').text("received connected")
            connected = true;
            connectHandler(socket);
        }
    }
}

function clickFunction(msg, jsonObj)
{
    var client = new RelayClient(config, jsonObj, function (socket) {
        socket.onmessage = function (event) {
            $('#div3').text(event.data)
        };
    });
}