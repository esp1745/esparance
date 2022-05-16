var http = require('http');
var fs = require('fs');
var index = fs.readFileSync( 'index.html');
const mysql =require('mysql')
 const connection = mysql.createConnection({
    host: 'localhost',
     user: 'root',
     password: '',
     database: 'temperaturedht'
  })
  

var SerialPort = require('serialport');
const parsers = SerialPort.parsers;

const parser = new parsers.Readline({
    delimiter: '\r\n'
});

var port = new SerialPort('COM8',{ 
    baudRate: 9600,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
    flowControl: false
});

port.pipe(parser);

var app = http.createServer(function(req, res) {
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.end(index);
});

var io = require('socket.io').listen(app);

io.on('connection', function(socket) {
    
    console.log('Node is listening to port');
    
});

parser.on('data', function(data) {
    try {
        connection.connect()
        var sql = "INSERT INTO dht(humidity,temperature) VALUES (5,7)";
        connection.query(sql, function (err, result) {
        //   if (err) throw err;
        console.log(err);
          console.log("1 record inserted");
        });
      
        
    } catch (error) {
        console.log(error)

        
    }
    connection.end()

    
    console.log('Received data from port: ' + data);
    
    io.emit('data', data);
    
});

app.listen(3000);
