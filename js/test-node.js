#!/usr/bin/env node

var passed = 0, failed = 0;

assert = require('assert');
function assert_eq(a, b)
{
	//console.log(a);
	//assert.deepStrictEqual(a, b)
	if ((aj = JSON.stringify(a)) != (bj = JSON.stringify(b))) {
		console.log("error: ", aj , "!=", bj)
		failed++;
	} else {
		passed++;
	}
}

function passed()
{
	console.log(4);
	console.log(__filename.slice(__dirname.length + 1));
}

var fs = require('fs')

function run_test(r)
{

	eval(fs.readFileSync('./' + r + '.js').toString());
	console.log(r + ".js, passed: ", passed, ", failed: ", failed);
	passed = 0, failed = 0;
}

run_test(7);
run_test(8);
run_test(9);
run_test(10);
