// ES9 - ECMAScript 2018 examples

[a, ...rest1] = [1, 2, 3];

assert_eq(rest1, [2, 3])

let {b, ...rest2} = { b: 1, c:2, d:3};
assert_eq(rest2, { c: 2, d: 3});

assert_eq([1, 2, ...[3, 4]], [1, 2, 3, 4]);

// https://github.com/tc39/proposal-async-iteration
var buff = '0'
async function process(array) {
  for await (let i of array) {
	  buff += String(i)
	  throw 'e'
  }
}

process([1, 2])
	.catch(a => {buff += a})
	.finally(() => {buff += 'f';
		assert_eq(buff, '01ef')});

/* Node.js only:
assert_eq(/(?<name>.)/.exec('1').groups.name, '1')
*/

// https://medium.com/@bramus/javascript-whats-new-in-ecmascript-2018-es2018-17ede97f36d5
// https://github.com/tc39/proposal-object-rest-spread
