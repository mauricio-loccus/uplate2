// app State
.pragma library

var connectedPC = false

function onlinePC() { return connectedPC }
function setOnlinePC(input) { connectedPC = input }
