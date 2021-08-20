import os
import sys

argv = sys.argv[1::]

class NotEnoughArgumentsError(Exception):
	pass

class UnknownArgumentError(Exception):
	pass

class Argument:
	def __init__(self):
		pass
	
	def set_value(self, value):
		self.value = value

	def get_value(self):
		return self.value

	def __str__(self):
		return self.get_value()

class ArgumentParser:
	def __init__(self, flag_arguments):
		self.flag_arguments = flag_arguments

	def __getitem__(self, key):
		return self.flag_arguments[key]
	def __setitem__(self, key, new_value):
		self.flag_arguments[key] = new_value

		return self.flag_arguments

	def parse(self, args):
		i = 0

		while i < len(args):
			try:
				arguments = self.flag_arguments[argv[i]]
				j = 0

				while j < len(arguments):
					if i + j + 1 == len(args):
						raise NotEnoughArgumentsError

					arguments[j].set_value(argv[i + j + 1])

					j = j + 1

				i = i + j
			except KeyError as ke:
				raise UnknownArgumentError
			except NotEnoughArgumentsError as neae:
				raise neae

			i = i + 1
				

arg_parser = ArgumentParser({ "-flag1" : [ Argument(), Argument(), Argument() ] })

arg_parser.parse(argv)

for flag, args in arg_parser.flag_arguments.items():
	print(flag + ": ")

	for arg in args:
		print("\t" + str(arg))