from NekPy.LibUtilities import SessionReader
from NekPy.SpatialDomains import MeshGraph
from NekPy.MultiRegions import ExpList2D
import ctypes
import gc
import sys

def get_refcount(coords_address):
	gc.collect()
	return ctypes.c_long.from_address(coords_address).value

def main():
	session_name = ["memory-test-python-to-c-address.py", "newsquare_2x2.xml"]

	session = SessionReader.CreateInstance(session_name)
	graph = MeshGraph.Read(session)
	exp = ExpList2D(session, graph)

	print("Loaded session: %s" % session.GetSessionName())
	print("Loaded MeshGraph of dimension: %d\n" % graph.GetMeshDimension())
	
	print("Retrieving coordinates...")
	coords = exp.GetCoords()
	coords = coords[0]
	coords_address = id(coords)	

	print("Retrieved coordinates.")
	print("Reference count for expansion coordinates: %d\n" % get_refcount(coords_address))

	print("Setting PhysArray (exp.SetPhysArray())...")
	exp.SetPhysArray(coords) 
	print("exp.SetPhysArray() completed.")
	print("Reference count for expansion coordinates: %d\n" % get_refcount(coords_address))
	
	print("Deleting coordinates in Python...")
	del coords
	gc.collect()
	print("Coordinates deleted in Python.")
	print("Reference count for expansion coordinates: %d\n" % get_refcount(coords_address))

	print("Attempting to calculate the integral...")
	print("Integral calculated to be: %r" % exp.PhysIntegral())

if __name__ == '__main__':
    main()
