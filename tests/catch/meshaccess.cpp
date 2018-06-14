
#include "catch.hpp"
#include <comp.hpp>

using namespace ngcomp;

#ifdef PARALLEL
const char * progname = "ngslib";
const char* ptrs[2] = { progname, nullptr };
const char** pptr = &ptrs[0];
static MyMPI mympi(1, (char**)pptr);
#endif

TEST_CASE ("ElementVolume", "[elementvolume]")
{
  netgen::printmessage_importance = 0;
  SECTION ("ElementVolume", "[elementvolume]")
    {
      for(int dim : {1,2,3})
	{
	  SECTION ("ElementVolume, dim = "+to_string(dim), "[elementvolume]")
	    {
	      string meshfile = dim==1 ? "line.vol" : (dim==2 ? "square.vol" : "cube.vol");
	      double elvol = dim==1 ? 1.0 : (dim==2 ? 1./2 : 1./12);
	      auto ma = MeshAccess(meshfile);
	      for(auto el : ma.Elements(VOL))
		{
		  CHECK(ma.ElementVolume(el.Nr()) == Approx(elvol).epsilon(1e-9));
		}
	    }
	}
    }
}

