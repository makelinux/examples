// ES8 - ECMAScript 2017 examples
// https://2ality.com/2016/02/ecmascript-2017.html
// https://flaviocopes.com/es2017/
// https://medium.com/@Rashaunwarner/new-es8-features-f3d8b7b4fc8c

// https://2ality.com/2015/11/stage3-object-entries.html
var map={'a':1, 'b':2}
assert_eq(Object.values(map), [1, 2])
assert_eq(Object.entries(map), [['a', 1], ['b', 2]])

// https://2ality.com/2015/11/string-padding.html
assert_eq('1'.padStart(3,0), '001')
assert_eq('loading'.padEnd(10, '. '), 'loading. .')
assert_eq(Object.getOwnPropertyDescriptors({a: 1}).a.writable, true)


function promise_func() {
	return new Promise((resolve, reject) => {
		setTimeout(() => {
			resolve('hello');
		}, 10);
	});
}

async function async_func() {
	const text = await promise_func();
	console.log(text);
}

async_func();

// TODO: SharedArrayBuffer, Atomics Object.prototype
// https://2ality.com/2017/01/shared-array-buffer.html
