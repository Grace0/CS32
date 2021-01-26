#  Design
I implemented a circular doubly-linked list with a dummy node. Each list node has a value, a pointer to the next node, and a pointer to the previous node in the list. This way, there are fewer edge cases to deal with, since a circular doubly-linked lists has no null pointers.
An empty list looks like this:

A typical list looks like this (this list has three nodes):

# Pseudocode

int insert(int pos, const ItemType& value);

int insert(const ItemType& value);

bool erase(int pos);

int remove(const ItemType& value);

void swap(Sequence& other);

int subsequence(const Sequence& seq1, const Sequence& seq2)

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) 

# Test Cases
## For Sequence class function implementations:
Sequence s;
Sequence e;

assert(s.empty() == 1); //test empty when empty
assert(s.size() == 0); //test size

assert(s.insert(0, 1) == 0); //insert at beginning of sequence
assert(s.empty() == 0); //test empty when not empty

assert(s.insert(1, 3) == 1); //insert at end of sequence
assert(s.insert(1, 2) == 1); //insert in middle of sequence
assert(s.insert(-1, 879) == -1); //pos out of bounds
assert(s.insert(907, 879) == -1); //pos out of bounds
assert(s.size() == 3); //test size
///1 2 3

assert(s.insert(4) == 3); //insert value greater than all current node values
assert(s.insert(4) == 3); //insert value greater than or equal to all current node values
//1 2 3 4 4
assert(s.size() == 5);
assert(s.insert(3) == 2); //insert a value less than some nodes but greater than other nodes
assert(s.insert(0) == 0); //insert a value less than all other nodes

assert(e.erase(0) == 0); //trying to erase from an empty list
assert(s.erase(-13) == 0); //erase invalid pos
assert(s.erase(988) == 0); //erase invalid pos

assert(s.erase(0) == 1); //erase first Node
assert(s.erase(1) == 1); //erase middle Node
assert(s.erase(2) == 1); //erase last Node
assert(s.size() == 4);

Sequence t;
t.insert(1);
t.insert(2);
t.insert(3);
t.insert(4);

//   Sequence u = t;
//   Sequence v(u);

unsigned long g = 0;
assert(t.get(0, g) == 1); //get first val
assert(g == 1);
assert(t.get(1, g) == 1);  //get middle val
assert(g == 2);
assert(t.get(2, g) == 1);  //get middle val
assert(g == 3);
assert(t.get(3, g) == 1);  //get last val
assert(g == 4);

assert(t.get(-88, g) == 0); //get invalid pos
assert(t.get(993, g) == 0); //get invalid pos
assert(e.get(34, g) == 0); //get from an empty list

t.set(0, 10); //set first Node val
t.set(1, 20); //set middle Node val
t.set(2, 30); //set middle Node val
t.set(3, 40); //set last Node val
assert(t.get(0, g) == 1);
assert(g == 10);
assert(t.get(1, g) == 1);
assert(g == 20);
assert(t.get(2, g) == 1);
assert(g == 30);
assert(t.get(3, g) == 1);
assert(g == 40);

assert(t.set(-249, 0) == 0); //set invalid pos
assert(t.set(9393, 38) == 0); //set invalid pos

assert(t.find(0) == -1); //val not found
assert(t.find(10) == 0); //val found at beginning
assert(t.find(20) == 1); //val found in middle
assert(t.find(30) == 2); //val found in middle
assert(t.find(40) == 3); //val found at end

assert(t.remove(348) == 0); //removes no values
assert(t.remove(10) == 1); //removes one value: the first value
t.insert(20);
assert(t.remove(20) == 2); //removes multiple values
assert(t.remove(40) == 1); //removes one value: the last value
assert(t.remove(30) == 1); //removes one value: the one remaining value

t.insert(1);
t.insert(1);
t.insert(1);
t.insert(1);
assert(t.remove(1) == 4); //remove all the values

t.insert(319);
t.insert(124);
t.swap(s); //swap two non-empty LL
assert(s.size() == 2);
assert(t.size() == 4);
s.swap(t);
assert(s.size() == 4);
assert(t.size() == 2);

e.swap(t); //swap one empty LL with one non-empty LL
assert(e.empty() == 0);
assert(t.empty() == 1);
t.swap(e);
assert(e.empty() == 1);
assert(t.empty() == 0);

Sequence e2;
e.swap(e2); //swap two empty LL
assert(e.empty() == 1);
assert(e2.empty() == 1); //test empty when empty

Sequence r = t; //copy constructor on a non-empty LL
Sequence w = e; //copy constructor on an empty LL

r = w; //call assignment operator to assign a non-empty LL to an empty LL
e = t; //call assignment operator to assign an empty LL to a non-empty LL

## For subsequence() and interleave():
Sequence s;
Sequence t;

s.insert(0,30);
s.insert(1,21);
s.insert(2,63);
s.insert(3,42);
s.insert(4,17);
s.insert(5,63);
s.insert(6,17);
s.insert(7,29);
s.insert(8,8);
s.insert(9,32);

t.insert(0,63);
t.insert(1,17);
t.insert(2,29);

assert(subsequence(s, t) == 5); //one possible k exists
assert(subsequence(t, s) == -1); //seq1.size < seq2.size

assert(subsequence(t, t) == 0); //subsequence of itself

Sequence u;
u.insert(0,63);
u.insert(1,17);
u.insert(2,29);
u.insert(3,42);
u.insert(4,17);
u.insert(5,63);
u.insert(6,17);
u.insert(7,29);
assert(subsequence(u, t) == 0); //subsequence() must return the *smallest* such k

Sequence v;
u.insert(0,6);
u.insert(1,1);
u.insert(2,2);
u.insert(3,4);
u.insert(4,1);
u.insert(5,6);
u.insert(6,1);
u.insert(7,2);
assert(subsequence(v, t) == -1); //no such k exists

Sequence p;
p.insert(0,30);
p.insert(1,21);
p.insert(2,63);
p.insert(3,42);

Sequence q;
q.insert(0,42);
q.insert(1,63);
q.insert(2,84);
q.insert(3,19);

Sequence r;
r.insert(0,3131);
r.insert(1,3107);

//if seq1 is empty
//if seq2 is empty
Sequence w;
Sequence x;
assert(subsequence(w, x) == -1);
assert(subsequence(x, w) == -1);

Sequence y;
interleave(w, x, y);
assert(y.empty() == true); //both seq1 and seq2 empty

Sequence z;
interleave(w, t, z);
assert(z.empty() == false); //seq1 empty, seq2 non-empty

Sequence aa;
interleave(t, w, aa);
assert(aa.empty() == false); //seq1 non-empty, seq2 empty

Sequence ab; // m = n
interleave(p, q, ab);

Sequence ac; // n = m
interleave(q, p, ac);

Sequence ad; // m > n
interleave(q, r, ad);

Sequence ae; // m < n
interleave(r, q, ae);

interleave(r, r, r); //seq1, seq2, result refer to the same Sequence

Sequence qa;
qa.insert(0,42);
qa.insert(1,63);
qa.insert(2,84);
qa.insert(3,19);

Sequence ra;
ra.insert(0,3131);
ra.insert(1,3107);
interleave(ra, qa, ra); //seq1 and result refer to the same Sequence


Sequence rb;
rb.insert(0,3131);
rb.insert(1,3107);
interleave(qa, rb, rb); //seq2 and result refer to the same Sequence

interleave(qa, qa, ra); //seq1 and seq2 refer to the same Sequence

Sequence af;
Sequence ag;
interleave(af, qa, ra); //seq1 is empty
interleave(qa, af, ra); //seq2 is empty
interleave(af, ag, ra); //both seq1 and seq2 are empty
