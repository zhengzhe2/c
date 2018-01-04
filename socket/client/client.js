var net = require('net');
var client = new net.Socket().setEncoding('utf-8');

//初始化并连接服务器
function InitSocket(host, port) {
    client.connect(port, host, function() {
        console.log('CONNECTED TO: ' + host + ':' + port);    
    });
}

function FinalSocket() {
    client.destroy();
}

function SendMessage(message) {
    console.log('send message :' + message);
    var buf =  Buffer.from(message);
    client.write(buf+'\0');
}


// 为客户端添加“data”事件处理函数
// data是服务器发回的数据
client.on('data', function(data) {
    var buf = Buffer.from(data);
    console.log('Callback  DATA: ' + buf);
    //调用CallBack函数，返回服务器处理后的值
});

// 为客户端添加“close”事件处理函数
client.on('close', function() {
    console.log('Connection closed');
});

client.on('error', function() {
    console.log('client connected error !!!!!');
    // 完全关闭连接
    client.destroy();
});

client.on('end', function() {
    console.log('client disconnected');    
});

module.exports = {
    InitSocket,
    FinalSocket,
    SendMessage
}

InitSocket('127.0.0.1', 6666);
SendMessage('sfdsfdsgdsgdsgd');






