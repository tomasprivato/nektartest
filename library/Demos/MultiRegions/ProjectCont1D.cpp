#include <cstdio>
#include <cstdlib>

#include <MultiRegions/ContExpList1D.h>

using namespace Nektar;

// compile using Builds/Demos/StdRegions -> make DEBUG=1 ProjectCont1D

// This routine projects a which has energy in all mdoes of the
// expansions and report an error.

int main(int argc, char *argv[])
{
    MultiRegions::ContExpList1DSharedPtr Exp,Sol;
    int     i,j,k;
    int     order, nq;
    int     coordim;
    char    *infile;
    LibUtilities::PointsType Qtype;
    LibUtilities::BasisType  btype;  
    Array<OneD,NekDouble> sol; 
    Array<OneD,NekDouble>  xc0,xc1,xc2; 

    if(argc != 5)
    {
        fprintf(stderr,"Usage: ProjectCont1D Type order nq  mesh \n");
        
        fprintf(stderr,"Where type is an integer value which "
                "dictates the basis as:\n");
        fprintf(stderr,"\t Modified_A = 4\n");
        fprintf(stderr,"\t GLL Lagrange   = 8\n");
        
        fprintf(stderr,"Note type = 1,2,4,5 are for higher dimensional basis\n");
        
        exit(1);
    }
    
    btype =   (LibUtilities::BasisType) atoi(argv[1]);
    
    // Check to see that only continuous 1D Expansions are used
    if((btype != LibUtilities::eModified_A)&&(btype != LibUtilities::eGLL_Lagrange))
    {
        NEKERROR(ErrorUtil::efatal,
                         "This basis is only for 1D Modified_A or GLL_Lagrange expansions");
    }
    
    // Do not use Fourier expansion
    if(btype == LibUtilities::eFourier)
    {
        NEKERROR(ErrorUtil::efatal,
                         "Demo not set up for Fourier Expanison");
    }
    
    order  =   atoi(argv[2]);
    nq     =   atoi(argv[3]);
    infile =   argv[4];
    
    Qtype = LibUtilities::eGaussLobattoLegendre; 
    
    // read in mesh
    string in(infile);
    SpatialDomains::MeshGraph1D graph1D; 
    graph1D.Read(in);
    
    // Define Expansion
    const LibUtilities::PointsKey Pkey(nq,Qtype);
    const LibUtilities::BasisKey Bkey(btype,order,Pkey);
    Exp = MemoryManager<MultiRegions::ContExpList1D>::AllocateSharedPtr(Bkey,graph1D.GetComposite(0));

    //----------------------------------------------
    // Define solution to be projected 
    coordim = Exp->GetCoordim(0);
    nq      = Exp->GetPointsTot();
    
    // define coordinates and solution
    sol = Array<OneD,NekDouble>(nq);
    
    xc0 = Array<OneD,NekDouble>(nq);
    xc1 = Array<OneD,NekDouble>(nq);
    xc2 = Array<OneD,NekDouble>(nq);
    
    switch(coordim)
    {
    case 1:
        Exp->GetCoords(xc0);
        Vmath::Zero(nq,&xc1[0],1);
        Vmath::Zero(nq,&xc2[0],1);
        break;
    case 2:
        Exp->GetCoords(xc0,xc1);
        Vmath::Zero(nq,&xc2[0],1);
        break;
    case 3:
        Exp->GetCoords(xc0,xc1,xc2);
        break;
    }
    
    for(i = 0; i < nq; ++i)
    {
        sol[i] = 0.0;
    for(j = 0; j < order; ++j)
    {
            sol[i] += pow(xc0[i],j);
            sol[i] += pow(xc1[i],j);
            sol[i] += pow(xc2[i],j);
    }
    }

    //----------------------------------------------
    // Setup Temporary expansion and put in solution
    Sol = MemoryManager<MultiRegions::ContExpList1D>::AllocateSharedPtr(*Exp);
    Sol->SetPhys(sol);
    //----------------------------------------------
  
    //---------------------------------------------
    // Project onto Expansion 
    Exp->FwdTrans(*Sol);
    //---------------------------------------------
    
    //-------------------------------------------
    // Backward Transform Solution to get projected values
    Exp->BwdTrans(*Exp);
    //-------------------------------------------  
    
    //--------------------------------------------
    // Write solution 
    ofstream outfile("ProjectContFile1D.dat");
    Exp->WriteToFile(outfile);
    //-------------------------------------------
    
    //--------------------------------------------
    // Calculate L_inf error 
    cout << "L infinity error: " << Exp->Linf(*Sol) << endl;
    cout << "L 2 error:        " << Exp->L2  (*Sol) << endl;
    //--------------------------------------------
    
    return 0;
}

