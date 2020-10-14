ans = [
    "()", #1
    "(b)", #2
    "(((((())))))", #3
    "ERROR: given string list is invalid (there are more ')' than '(' )\n\
string value = [(a(b)))]", #4
    "ERROR: given string list is invalid (there are more '(' than ')' )\n\
string value = [(a((b)c)]", #5
    "ERROR: given string list is invalid (it has to start with '(' )\n\
string value = [abc]", #6
    "(a(((f(hg)k))d)e)", #7
    "((c(de)f))", #8
    "(a((c(e(kg))h)j)k)", #9
    "(a(b(c)d))", #10
]

for i in range(1, 11):
    f = open(f"Tests/test{i}.txt", 'r')
    inp = f.read()
    print(f"Starting test{i}:", f"[{inp}]");
    f.close()
    f = open(f"Tests/testres{i}.txt", 'r')
    myRes = f.read()
    f.close()
    trueRes = ans[i-1]
    if myRes == trueRes:
        print(f"\033[32mtest{i} completed successfully\033[m\n")
    else:
        print(f"\033[31mtest{i} failed:\033[m", \
            f"your res = [{myRes}]", \
                f"true res = [{trueRes}]", sep='\n', end='\n\n')