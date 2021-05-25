const express = require('express'),
path = require('path')

const addon = require('./build/Release/addon');

const bodyParser = require('body-parser');
const app = express();

const port = 3000

function MatrixString(dict, matSize, matLetter)
{
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
function ConvertDictToString(dict)
{
  var str = "";
  str += dict["type"] + " ";
  var matASize = dict["MatrixASize"].split("x");
  var matBSize = dict["MatrixBSize"].split("x");

  str += MatrixString(dict, matASize, "A");
  str += MatrixString(dict, matBSize, "B");
  return str
}


app.use(bodyParser.urlencoded({ extended: true }));

app.set('view engine', 'ejs');
app.set('views', path.resolve( __dirname, 'views'));


app.get('/tutorial', function (req, res) {
  res.render('tutorial', {})
})

app.post('/tutorial', function(req, res){
    console.log(req.body);
});

app.get('/simplex', function(req, res) {
  res.render('simplex', {})
})

app.get('/matrix', function(req, res) {
  res.render('matrix', {})
})

app.post('/matrix', function(req, res){
  console.log(req.body);
  var inputstring = ConvertDictToString(req.body);
  var output = addon.main(inputstring);
});

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})
