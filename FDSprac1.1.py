print("Enter two matrix for Addition ,Subtraction and Multiplication\n")
r1=int(input("Entre the row of A matrix\n"))
c1=int(input("entre the column of A matrix\n"))
r2=int(input("Entre the row of B matrix\n"))
c2=int(input("entre the column of B matrix\n"))

a=[]
for i in range(r1):
	w=[]
	for j in range(c1):
		w.append(int(input(f"Entre the value of A [{i}][{j}]")))
	a.append(w)
print("A=")
for r1a in a:
	print(r1a)
print("*********************")
b=[]
for i in range(r2):
	x=[]
	for j in range(c2):
		x.append(int(input(f"Entre the value of B [{i}][{j}] ")))
	b.append(x)
		
print("B=")
for r2b in b:
	print(r2b)
print("****************")
print("Choose the option for that operation\n")
print("1.Addition\n")
print("2.Subtraction\n")
print("3.multiplcation\n")
print("4.transpose")
c=int(input("Entre here :"))
if (c==1):
	if ((r1==r2)and(c1==c2)):
		sum=[]
		for i in range(r1):
			y=[]
			for j in range(r2):
				val=a[i][j]+b[i][j]
				y.append(val)
			sum.append(y)
	    	
	for r1sum in sum:
				print(r1sum)
				
	#else:
	#	print("add not")
elif(c==2):
	if ((r1==r2)and(c1==c2)):
		sub=[]
		for i in range(r1):
			z=[]
			for j in range(r2):
				valu=a[i][j]-b[i][j]
				z.append(valu)
			sub.append(z)
	    	
	for r1sub in sub:
				print(r1sub)
	#else:
	#	print("sub not")
elif(c==3):
	if(c1==r2):
		mul=[]
		for i in range(r1):
			s=[]
			for j in range(c2):
				s.append(0)
			mul.append(s)
		for i in range(r1):
			for j in range(c2):
				for k in range(r2):
					mul[i][j]+=a[i][k]*b[k][j]
		for rm in mul:
			print(rm)
	
	
elif(c==4):
	g=int(input("chose 1 for matrix A and 2 for matrix B"))
	if(g==1):
		trans1=[]
		for i in range(c1):
			u=[]
			for j in range(r1):
				u.append(0)
			trans1.append(u)
			
		for i in range(r1):
			for j in range(c1):
				trans1[j][i]=a[i][j]
				
		for r1trans1 in trans1:
			print(r1trans1)
	else:
		trans2=[]
		for i in range(c2):
			h=[]
			for j in range(r2):
				h.append(0)
			trans2.append(h)
			
		for i in range(r2):
			for j in range(c2):
				trans2[j][i]=b[i][j]
				
		for r2trans2 in trans2:
			print(r2trans2)
		
