// initial thought since jump in diffculty caught me bit off guard
// -> we have 256 different boxes (hashed of given label?)
// -> and every box has their own multiplier?
//      -> in every box we have lenses


//  "rn=1 is 30"
// rn is label, hashed tells us which box to be placed
// '=' or '-' tells us is the operation insertion or delete
// -> if '='
//      -> there is no lens with same hash, we add lens[30] with focal strength of 1
//      -> if there is already lens with hash 30, we modify focal value to 30 (replace the lens)
// -> if '-'
//      -> if there is lens in box.lens[30] we delete it?
//      -> if not "nothing interesting happens"

// so general idea:
//
// 1. Loop
//     1.1 take label until we get to - or =
//     1.2 take next value (1-9) and save it as focal strengt
//     1.3 send these variables to be either added or deleted function


// 2. addition
//     2.1 hash the label to get box where it belong
//     2.2 loop to check if there is already lens with this label
//     2.3 if yes, we update box->lens->focal
//     2.4 if not, we copy this new label and its focal into box array

// 3. deletion
//     3.1 hash the label to get box where it belong
//     3.2 loop to check if there is matching
//     3.3 if yes, we move everything from that point up front by one?
//     3.4 if not, we just simply ignore and start with next input

// 4. result
//      4.1 loop thru boxes (that has length)
//      4.2 we take values of box number * lens index (not hash) * focal of this lens
//      4.3 sum this to total value
//      4.4 return total