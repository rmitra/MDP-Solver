import sys
import random
import math

class MDP:
	def __init__(self):
		self.S = 0
		self.A = 0

	def load_MDP_data(self, filename):
		fp = open(filename, 'r')
		
		self.S = int(fp.readline().strip("\n"))
		self.A = int(fp.readline().strip("\n"))
		
		self.R = [[[] for a in range(self.A)] for s in range(self.S)]
		self.T = [[[] for a in range(self.A)] for s in range(self.S)]
		
		for s in range(0,self.S):
			for a in range(0, self.A):
				self.R[s][a] = fp.readline().strip("\n").split("\t")

		for s in range(0,self.S):
			for a in range(0, self.A):
				self.T[s][a] = fp.readline().strip("\n").split("\t")

		self.Gamma = float(fp.readline().strip("\n"))
		self.V = [0.0] * self.S
		self.P = [0] * self.S


	def display_MDP_data(self):
		print "State :" + str(self.S)
		print "Action :" + str(self.A)
		
		print "Reward"

		for s in range(self.S):
			for a in range(self.A):
				for sp in range(self.S):
					print str(self.R[s][a][sp]) + " ",
				print "\n",

		print "Transition"
		
		for s in range(self.S):
			for a in range(self.A):
				for sp in range(self.S):
					print str(self.T[s][a][sp]) + " ",
				print "\n",

		print "Gamma :" + str(self.Gamma)
		print "V :" + str(len(self.V))
		print self.V
		print "P :" + str(len(self.P))
		print self.P


	def display_opt(self):
		for s in range(self.S):
			print str(self.V[s]) + " " + str(self.P[s])


	def compute_max(self, s):
		max_value = -999999.0
		
		for a in range(self.A):
			exp_value = 0.0
			for sp in range(self.S):
				exp_value = exp_value + float(self.T[s][a][sp]) * (float(self.R[s][a][sp]) + self.Gamma * self.V[sp])
			
			if exp_value > max_value:
				max_value = exp_value
				self.P[s] = a
		
		return max_value

	def solve_MDP(self, eph):
		converged = False;
		
		while converged == False:
			max_diff = -1.0
			
			for s in range(self.S):
				old_value = self.V[s]
				self.V[s] = self.compute_max(s)
				new_value = self.V[s]

				if math.fabs(new_value - new_value) > max_diff:
					max_diff = math.fabs(new_value - old_value)

			if (max_diff <= eph):
				converged = True


filename = sys.argv[1]

m = MDP()
m.load_MDP_data(filename)
#m.display_MDP_data()
m.solve_MDP(0.0000001)
m.display_opt()
