
from sympy import *


###################################################################################################

"""Q1::Given a Matrix and a real value.you need to verify that given real value is Eigen value of a
given matrix."""


def is_eigen_value(a,b):
    
    length = (len(a))          # calculate the size of matrix
    
    x = (eye(length))            #identity matrix
    
    x = b*x                   # identity scalar muoltiply  
    
    a = Matrix(a)              # convert list to matrix
    
    y = a-x
    
    y = y.rref()            #reduce echelon
    
    pprint(y)
    
    free_variable = y[1]       #free variables
    print(y[1])
    if len(free_variable) == length:
        print(b , " is not eigenvalue")
    else:
        print(b, " is eigenvalue")
    

a = [[1,6],[5,2]]
is_eigen_value(a,i)




#####################################################################################################


""" Q2::Given a Matrix and a vector .you need to verify that given vector is Eigen vector of a given
matrix."""


def is_eign_vector(matrix,vector):
    
    matrix = Matrix(matrix)
        
    vector = Matrix(vector)
    
    y = matrix * vector 
    
    y = list(y)
    
    mini = abs(min(list(y)))
    
    for i in range(mini,2,-1):
        
        flage = 1
        
        for j in y:
            
            if abs(j) % i == 0:
                flage += 1
                
        if flage == len(vector):
            print("Given vector is Eign_vector")
            return 
        else:
            print("Given vector is not Eign_vector")
            return
        
a = [[1,6],[5,2]]
v = [6,-3]
is_eign_vector(a,v)

#################################################################################################


"""Q3::Given a Matrix compute the Eigen values"""


def compute_Eigenvalues(matrix):
    
    length = len(matrix)
    
    matrix = Matrix(matrix)
    
    x = Symbol("lambda")         #  'lambda'
    
    identity = x * eye(length) 
    
    eigen_values = matrix - identity
    
    eigen_values = eigen_values.det()
    
    eigen_values = solve(eigen_values)
  
    return eigen_values


a = [[1,6],[5,2]]
compute_Eigenvalues(a)


#########################################################################################################

"""Q4::Given a Matrix and Eigen vector.you need to compute the Eigen value corresponding to given
Eigen vector."""

def is_eign_vector(matrix,vector):
    
    matrix = Matrix(matrix)
        
    vector = Matrix(vector)
    
    y = matrix * vector 
    
    y = list(y)
    
    mini = abs(min(list(y)))
    
    for i in range(mini,2,-1):
        
        flage = 1
        
        for j in y:
            
            if abs(j) % i == 0:
                flage += 1
                
        if flage == len(vector):
            print("Given vector is Eign_value")
            return 
        else:
            print("Given vector is not Eign_value")
            return
