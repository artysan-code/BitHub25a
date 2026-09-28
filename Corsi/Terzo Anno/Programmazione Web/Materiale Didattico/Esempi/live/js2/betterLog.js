const debug = function(txt) {
    console.log("DEBUG - " + txt);
}


const error = function(txt){
    console.error("ERROR - " + txt);
}

exports.debug = debug;
exports.error = error;