The algorithm as described at http://en.wikipedia.org/wiki/Weasel_program

1. Start with a random string of 28 characters.
2. Make 100 copies of this string, with a 5% chance per character of that
   character being replaced with a random character.
3. Compare each new string with "METHINKS IT IS LIKE A WEASEL", and give
   each a score (the number of letters in the string that are correct and
   in the correct position).
4. If any of the new strings has a perfect score (== 28), halt.
5. Otherwise, take the highest scoring string, and go to step 2.

This program parametrizes the number of copies, mutation threshold and
of course the target phrase.

By Jaldhar H. Vyas <jaldhar@braincells.com>
(C) 2016 Consolidated Braincells Inc.  All rights reserved.
"Do What Thou Wilt" Shall Be The Whole Of The License.
