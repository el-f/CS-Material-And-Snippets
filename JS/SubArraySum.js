/*
Problem Statement:
----------------------------------------------------------------------------------
A subarray of an array is a consecutive sequence of zero or more 
values taken out of that array. For example, the array [1, 3, 7] has 
seven subarrays:
[ ]    [1]   [3]   [7]   [1, 3]   [3, 7]   [1, 3, 7]

Notice that [1, 7] is not a subarray of [1, 3, 7], because even 
though the values 1 and 7 appear in the array, they're not consecutive 
in the array. Similarly, the array [7, 3] isn't a subarray of the 
original array, because these values are in the wrong order.

The sum of an array is the sum of all the values in that array. 
Your task is to write a function that takes as input an array and 
utputs the sum of all of its subarrays. For example, given [1, 3, 7], 
you'd output 36, because

[ ] + [1] + [3] + [7] + [1, 3] + [3, 7] + [1, 3, 7] =
0 + 1 + 3 + 7 + 4 + 10 + 11 = 36


Possible Follow­Up Questions:
• Is the array necessarily sorted? No, it's not necessarily sorted.
• Can the array contain duplicate values? Yes, it might.
• Do we have to worry about integer overflow? No, don't worry about that.
• Are there any bounds on the number of elements in the array? No, there isn't.
• How do we handle the empty array? The sum of zero numbers is zero.

----------------------------------------------------------------------------------
Link: https://web.stanford.edu/class/cs9/sample_probs/SubarraySums.pdf
*/

var arr = [1, 3, 7];

// Option 1: Brute force O(n^3)
function subarraySum(arr) {
  let result = 0;
  for (let i = 0; i < arr.length; i++) {
    for (let j = i; j < arr.length; j++) {
      for (let k = i; k <= j; k++) {
        result += arr[k];
      }
    }
  }
  return result;
}

console.log(subarraySum(arr));

// Option 2: Optimized Subarray Enumeration O(n^2)
function subarraySum2(arr) {
  let result = 0;
  for (let i = 0; i < arr.length; i++) {
    let sum = 0;
    for (let j = i; j < arr.length; j++) {
      sum += arr[j];
      result += sum;
    }
  }
  return result;
}

console.log(subarraySum2(arr));

// Option 3: Regrouping the Sum
function subarraySum3(arr) {
  let result = 0;
  for (let i = 0; i < arr.length; i++) {
    result += arr[i] * (i + 1) * (arr.length - i);
  }
  return result;
}

console.log(subarraySum3(arr));
