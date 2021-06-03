const express = require('express'),
path = require('path')

const addon = require('./build/Release/addon');

const bodyParser = require('body-parser');
const app = express();

const port = 3000

/*function ConvertStringToMat(chararray)
{
  var index = 0;
  var matrows = chararray[index];
  index++;
  var matcols = chararray[index];
  index++;

  var mat = new Array(matcols);

  for (var i = 0; i < matcols; i++)
  {
    mat[i] = new Array(matrows);
    for (var j = 0; j < matrows; j++)
    {
      mat[i][j] = parseFloat(chararray[index]);
      index++;
    }
  }
  return mat;
} */


function MatrixString(dict, matLetter)
{
  //console.log("test log: " + dict["Matrix" + matLetter + "Size"]);
  var matSize = dict["Matrix" + matLetter + "Size"].split("x");
  var str = "";
  str += matSize[0] + " " + matSize[1] + " "
  for (var i = 0; i < matSize[1]; i++)
  {
    for (var j = 0; j < matSize[0]; j++)
    {
      str += dict[matLetter + "_" + i + "_" + j] + " ";
    }
  }
  return str
}


app.use(bodyParser.urlencoded({ extended: true }));

app.set('view engine', 'ejs');
app.set('views', path.resolve( __dirname, 'views'));

app.get('/simul', function(req, res) {

  res.render('simul', {matrixAString: "", message: "", result: ""});

})


app.get('/', function(req, res) {

res.render('menu', {});

})


app.post('/simul', function(req, res){
  console.log(req.body);
  var matrixAString = MatrixString(req.body, "A");
  var inputstring = "Simul " + req.body["type"] + " " + matrixAString;
  console.log("inputstring: " + inputstring);
  var outputstring = addon.main(inputstring);
  //console.log("outputstring: " + outputstring);
  //var outputmatrix = ConvertStringToMat(outputstring.split(" "));
  if (outputstring.split(" ")[0] == "Error:")
  {
    console.log(outputstring);
    res.render('simul', {matrixAString: matrixAString, message: outputstring, result: ""});
  }
  else {
    res.render('simul', {matrixAString: matrixAString, message:"", result: outputstring});

  }
})

app.get('/simplex', function(req, res) {

  res.render('simplex', {matrixAString: "", message: "", result: ""});

})

app.post('/simplex', function(req, res){
  console.log(req.body);
  var matrixAString = MatrixString(req.body, "A");
  var inputstring = "Simplex " + req.body["type"] + " " + req.body["numofvar"] + " " + req.body["numofslackvar"] + " " + req.body["numofartificialvar"] + " " + matrixAString;
  console.log("inputstring: " + inputstring);
  var outputstring = addon.main(inputstring);
  //console.log("outputstring: " + outputstring);
  //var outputmatrix = ConvertStringToMat(outputstring.split(" "));
  if (outputstring.split(" ")[0] == "Error:")
  {
    console.log(outputstring);
    res.render('simplex', {matrixAString: matrixAString, message: outputstring, result: ""});
  }
  else {
    res.render('simplex', {matrixAString: matrixAString, message:"", result: outputstring});

  }
})

app.get('/matrix', function(req, res) {

res.render('matrix', {matrixAString: "", matrixBString: "", matrixCString: "", message: ""});

})

app.post('/matrix', function(req, res){
  console.log(req.body);
  var matrixAString = MatrixString(req.body, "A");
  var matrixBString = MatrixString(req.body, "B");
  var inputstring = "Matrix " + req.body["type"] + " " + matrixAString + matrixBString + req.body["cVal"] + " " + req.body["i"] + " " + req.body["j"];
  console.log("inputstring: " + inputstring);
  var outputstring = addon.main(inputstring);
  //console.log("outputstring: " + outputstring);
  //var outputmatrix = ConvertStringToMat(outputstring.split(" "));
  if (outputstring.split(" ")[0] == "Error:" || outputstring.split(" ")[0] == "Det:")
  {
    console.log(outputstring);
    res.render('matrix', {matrixAString: matrixAString, matrixBString: matrixBString, matrixCString: "", message: outputstring});
  }
  else {
    res.render('matrix', {matrixAString: matrixAString, matrixBString: matrixBString, matrixCString: outputstring, message:""});

  }
})

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})

process.on('uncaughtException', function (err) {
  console.error((new Date).toUTCString() + ' uncaughtException:', err.message)
  console.error(err.stack)
  process.exit(1)
})
