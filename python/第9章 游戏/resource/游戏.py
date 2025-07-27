print('abcab'.replace('a','yy'))
table=''.maketrans('abcw','xyzc')
print('Hellow world'.translate(table))
print('hello world,hellow every one'.replace('hello','hi'))
vec=[[1,2],[3,4]]
print([col for row in vec for col in row])
vec=[[1,2],[3,4]]
print([[row[i] for row in vec] for i in range(len(vec[0]))])
x=[1,2]
print(list(enumerate(x)))
x=[3,5,3,7]
print([x.index(i) for i in x if i==3])