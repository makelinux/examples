// ES9 - ECMAScript 2018
// https://medium.com/@bramus/javascript-whats-new-in-ecmascript-2018-es2018-17ede97f36d5

// https://github.com/tc39/proposal-object-rest-spread

[ a, ...rest1 ] = [ 1, 2, 3 ];

assert_eq(rest1, [ 2, 3 ])

let {b, ...rest2} = { b: 1, c:2, d:3 };
assert_eq(rest2, { c: 2, d: 3 });

assert_eq([ 1, 2, ...[ 3, 4 ] ], [ 1, 2, 3, 4 ]);

// https://github.com/tc39/proposal-async-iteration

// Promise.prototype.finally() and additions to RegExp

// TODO
