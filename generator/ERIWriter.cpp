#include <ostream>

#include "generator/Classes.hpp"


void DeclareContwork(std::ostream & os, const ERIGeneratorInfo & info)
{
    if(info.ContMemoryReq() == 0)
        return;

    size_t contmem = info.ContMemoryReq();

    os << indent1 << "//Workspace for contracted integrals\n";
    if(info.UseHeap())
        os << indent1 << "double * const constwork = ALLOC(SIMINT_NSHELL_SIMD * " << contmem << ");\n\n";
    else
        os << indent1 << "double contwork[SIMINT_NSHELL_SIMD * " << contmem << "] SIMINT_ALIGN_ARRAY_DBL;\n\n";

    os << indent1 << "// partition workspace into shells\n";
    size_t ptidx = 0;

    for(const auto & it : info.GetContQ())
    {
        if(!info.IsFinalAM(it))
        {
            os << indent1 << "double * const " << ArrVarName(it) << " = contwork + (SIMINT_NSHELL_SIMD * " << ptidx << ");\n";
            ptidx += NCART(it);
        }
    }

    os << "\n";

}


void ZeroContWork(std::ostream & os, const ERIGeneratorInfo & info)
{
    size_t contmem = info.ContMemoryReq();
    if(contmem > 0)
        os << indent3 << "memset(contwork, 0, SIMINT_NSHELL_SIMD * " << contmem << ");\n";
    
}


void FreeContWork(std::ostream & os, const ERIGeneratorInfo & info)
{
    size_t contmem = info.ContMemoryReq();

    if(contmem > 0 && info.UseHeap())
    {
        os << indent1 << "// Free contracted workspace\n";
        os << indent1 << "FREE(contwork);\n\n";
    }       
}

void WriteFile_Permute(std::ostream & os)
{
    QAM am = WriterInfo::FinalAM();
    QAM tocall = am;

    bool swap_ab = false;
    bool swap_cd = false;

    // TODO - more thoroughly check?
    if(am[0] == 0)
    {
        swap_ab = true;
        std::swap(tocall[0], tocall[1]);
    }
    if(am[2] == 0)
    {
        swap_cd = true;
        std::swap(tocall[2], tocall[3]);
    }

    std::stringstream ss;
    ss << "int eri_"
       << amchar[am[0]] << "_" << amchar[am[1]] << "_"
       << amchar[am[2]] << "_" << amchar[am[3]] << "(";

    std::string funcline = ss.str();
    std::string indent(funcline.length(), ' ');

    // start output to the file
    os << "#include \"eri/eri.h\"\n";
    os << "\n";

    // rest of includes are not needed

    os << "\n\n";
    os << funcline;
    os << "struct multishell_pair P,\n";
    os << indent << "struct multishell_pair Q,\n";
    os << indent << "double * const restrict " << ArrVarName(am) << ")\n";
    os << "{\n";
    os << indent1 << "// Can be accomplished by swapping some variables\n";
    os << indent1 << "// and calling another function\n";
    os << indent1 << "// Note that the struct was passed by copy\n";
    os << "\n";
    os << indent1 << "double * tmp;\n";
    if(swap_ab)
    {
        os << indent1 << "tmp = P.PA_x;   P.PA_x = P.PB_x;   P.PB_x = tmp;\n";
        os << indent1 << "tmp = P.PA_y;   P.PA_y = P.PB_y;   P.PB_y = tmp;\n";
        os << indent1 << "tmp = P.PA_z;   P.PA_z = P.PB_z;   P.PB_z = tmp;\n";
    }
    if(swap_cd)
    {
        os << indent1 << "tmp = Q.PA_x;   Q.PA_x = Q.PB_x;   Q.PB_x = tmp;\n";
        os << indent1 << "tmp = Q.PA_y;   Q.PA_y = Q.PB_y;   Q.PB_y = tmp;\n";
        os << indent1 << "tmp = Q.PA_z;   Q.PA_z = Q.PB_z;   Q.PB_z = tmp;\n";
    }

    os << indent1 << "return eri_" << amchar[tocall[0]] << "_" 
                                   << amchar[tocall[1]] << "_" 
                                   << amchar[tocall[2]] << "_" 
                                   << amchar[tocall[3]] << "(P, Q, " << ArrVarName(am) << ");\n"; 


    os << "}\n";
    os << "\n";
}


void WriteFile(std::ostream & os,
               ERIGeneratorInfo & info,
               const BoysGen & bg,
               const VRR_Writer & vrr_writer,
               const ET_Writer & et_writer,
               const HRR_Writer & hrr_writer)
{
    const int ncart = NCART(am);

    


    // some helper bools
    bool hashrr = hrr_writer.HasHRR();
    bool hasbrahrr = hrr_writer.HasBraHRR();
    bool haskethrr = hrr_writer.HasKetHRR();
    bool inline_hrr = (hashrr && WriterInfo::GetOption(Options::InlineHRR) != 0);

    bool hasbravrr = vrr_writer.HasBraVRR();
    bool hasketvrr = vrr_writer.HasKetVRR();

    bool haset = et_writer.HasET();
    bool hasbraet = et_writer.HasBraET(); 
    bool hasketet = et_writer.HasKetET(); 

    bool hasoneoverp = (hasbravrr || hasbraet);
    bool hasoneoverq = (hasketvrr || hasketet);
    bool hasoneover2p = (hasbraet || (hasbravrr && (am[0]+am[1]) > 1)); 
    bool hasoneover2q = (hasketet || (hasketvrr && (am[2]+am[3]) > 1)); 
    bool hasoneover2pq = haset info::GetOption(Options::NoET) && 
                         (am[0] + am[1] > 0) && (am[2] + am[3] > 0);


    // load this once here
    const VectorInfo & vinfo = info.GetVectorInfo();

    std::string dbltype = vinfo::DoubleType();
    std::string cdbltype = vinfo::ConstDoubleType();

    // we need a constant one for 1/x
    info::AddIntegerConstant(1);

    // add includes
    info.AddInclude("<string.h>");
    info.AddInclude("<math.h>");
    info.AddInclude("\"eri/eri.h\"");
    bg.AddIncludes(info);

    // add constants
    bg.AddConstants(info);
    et_writer.AddConstants(info);
    vrr_writer.AddConstants(info);
    hrr_writer.AddConstants(info);

    // need these factors sometimes
    if(hasoneover2p || hasoneover2q || hasoneover2pq)
        info.AddNamedConstant("one_half", "0.5");



    ///////////////////////////////////////
    // Beginning of file writing
    ///////////////////////////////////////

    // Write out all the includes
    for(const auto & it : info.GetIncludes())
        os << "#include " << it << "\n";


    //////////////////////////////
    // Function name & signature
    //////////////////////////////
    std::stringstream ss;
    ss << "int eri_"
       << amchar[am[0]] << "_" << amchar[am[1]] << "_"
       << amchar[am[2]] << "_" << amchar[am[3]] << "(";


    std::string funcline = ss.str();
    std::string indent(funcline.length(), ' ');


    os << "\n\n";
    os << funcline;
    os << "struct multishell_pair const P,\n";
    os << indent << "struct multishell_pair const Q,\n";
    os << indent << "double * const restrict " << ArrVarName(am) << ")\n";
    os << "{\n";
    os << "\n";


    ///////////////////////////////////
    // NOW IN THE ACTUAL ERI FUNCTION
    ///////////////////////////////////

    // If there is no HRR, integrals are accumulated from inside the primitive loop
    // directly into the final integral array that was passed into this function, so it must be zeroed first
    if(!hashrr)
        os << indent1 << "memset(" << ArrVarName(am) << ", 0, P.nshell12 * Q.nshell12 * " << ncart << " * sizeof(double));\n";
    os << "\n";


    // abcd = index within simd loop, 
    os << indent1 << "int ab, cd, cdbatch, abcd;\n";
    os << indent1 << "int istart, jstart;\n";
    os << indent1 << "int iprimcd, nprim_icd, icd;\n";
    os << indent1 << "int i, j, n;\n";

    // real_abcd is the absolute
    // full abcd in terms of all the shells that we are doing
    if(hashrr)
        os << indent1 << "int real_abcd;\n";


    // Needed for determining offsets
    // But that's only if we are vectorizing
    if(Vectorized())
        os << indent1 << "int np;\n";
    

    // Needed only if we are doing inline HRR
    if(inline_hrr)
    {
        if(hasbrahrr)
            os << indent1 << "int iket;\n";
        if(haskethrr)
            os << indent1 << "int ibra;\n";
    }

    os << "\n";

    // Declare the temporary space 
    if(hashrr)
        DeclareContwork(os);



    // Write out all the constants 
    WriterInfo::WriteConstants(os);

    


    os << "\n\n";
    os << indent1 << "////////////////////////////////////////\n";
    os << indent1 << "// Loop over shells and primitives\n";
    os << indent1 << "////////////////////////////////////////\n";
    os << "\n";
    if(hashrr)
        os << indent1 << "real_abcd = 0;\n";
    else
        os << indent1 << "abcd = 0;\n";

    os << indent1 << "istart = 0;\n";
    os << indent1 << "for(ab = 0; ab < P.nshell12; ++ab)\n";
    os << indent1 << "{\n";

    os << indent2 << "const int iend = istart + P.nprim12[ab];\n";
    os << "\n";

    os << indent2 << "cd = 0;\n";
    os << indent2 << "jstart = 0;\n";
    os << "\n";

    os << indent2 << "for(cdbatch = 0; cdbatch < Q.nbatch; ++cdbatch)\n";
    os << indent2 << "{\n";
    os << indent3 << "const int nshellbatch = ((cd + SIMINT_NSHELL_SIMD) > Q.nshell12) ? Q.nshell12 - cd : SIMINT_NSHELL_SIMD;\n";

    os << indent3 << "const int jend = jstart + Q.nbatchprim[cdbatch];\n";


    if(hashrr)
    {
        WriterInfo::ZeroContWork(os);
        os << indent3 << "abcd = 0;\n";
        os << "\n";
    }

    os << indent3 << "for(i = istart; i < iend; ++i)\n";
    os << indent3 << "{\n";
    os << "\n";

    os << indent4 << "icd = 0;\n";
    os << indent4 << "iprimcd = 0;\n";
    os << indent4 << "nprim_icd = Q.nprim12[cd];\n";

    vrr_writer.DeclarePrimPointers(os);
    os << "\n";
    et_writer.DeclarePrimPointers(os);
    os << "\n";

    os << indent4 << "// Load these one per loop over i\n";
    os << indent4 << WriterInfo::NewConstDoubleSet1("P_alpha", "P.alpha[i]") << ";\n";
    os << indent4 << WriterInfo::NewConstDoubleSet1("P_prefac", "P.prefac[i]") << ";\n";
    os << indent4 << WriterInfo::NewConstDoubleSet1("P_x", "P.x[i]") << ";\n";
    os << indent4 << WriterInfo::NewConstDoubleSet1("P_y", "P.y[i]") << ";\n";
    os << indent4 << WriterInfo::NewConstDoubleSet1("P_z", "P.z[i]") << ";\n";

    if(hasbravrr)
    {
        if(WriterInfo::HasVRR_I())
        {
            os << indent4 << WriterInfo::NewConstDoubleSet1("P_PA_x", "P.PA_x[i]") << ";\n";
            os << indent4 << WriterInfo::NewConstDoubleSet1("P_PA_y", "P.PA_y[i]") << ";\n";
            os << indent4 << WriterInfo::NewConstDoubleSet1("P_PA_z", "P.PA_z[i]") << ";\n";
        }
        else
        {
            os << indent4 << WriterInfo::NewConstDoubleSet1("P_PB_x", "P.PB_x[i]") << ";\n";
            os << indent4 << WriterInfo::NewConstDoubleSet1("P_PB_y", "P.PB_y[i]") << ";\n";
            os << indent4 << WriterInfo::NewConstDoubleSet1("P_PB_z", "P.PB_z[i]") << ";\n";
        }
    }

    if(hasketet)
    {
        os << indent4 << WriterInfo::NewConstDoubleSet1("P_bAB_x", "P.bAB_x[i]") << ";\n";
        os << indent4 << WriterInfo::NewConstDoubleSet1("P_bAB_y", "P.bAB_y[i]") << ";\n";
        os << indent4 << WriterInfo::NewConstDoubleSet1("P_bAB_z", "P.bAB_z[i]") << ";\n";
    }

    os << "\n";


    os << indent4 << "for(j = jstart; j < jend; j += SIMINT_SIMD_LEN)\n";
    os << indent4 << "{\n";

    if(!WriterInfo::Scalar() && WriterInfo::Intrinsics())
        WriterInfo::WriteShellOffsets(os);
    else
        WriterInfo::WriteShellOffsets_Scalar(os);

    os << "\n";

    vrr_writer.DeclarePrimArrays(os);
    et_writer.DeclarePrimArrays(os);

    os << indent5 << WriterInfo::NewConstDoubleLoad("Q_alpha", "Q.alpha", "j") << ";\n";
    os << indent5 << cdbltype << " PQalpha_mul = P_alpha * Q_alpha;\n";
    os << indent5 << cdbltype << " PQalpha_sum = P_alpha + Q_alpha;\n";
    os << indent5 << cdbltype << " one_over_PQalpha_sum = " << WriterInfo::NamedConstant("const_1") << " / PQalpha_sum;\n";
    os << "\n";
    os << "\n";
    os << indent5 << "/* construct R2 = (Px - Qx)**2 + (Py - Qy)**2 + (Pz -Qz)**2 */\n";
    os << indent5 << cdbltype << " PQ_x = P_x - " << WriterInfo::DoubleLoad("Q.x", "j") << ";\n";
    os << indent5 << cdbltype << " PQ_y = P_y - " << WriterInfo::DoubleLoad("Q.y", "j") << ";\n";
    os << indent5 << cdbltype << " PQ_z = P_z - " << WriterInfo::DoubleLoad("Q.z", "j") << ";\n";


    os << indent5 << cdbltype << " R2 = PQ_x*PQ_x + PQ_y*PQ_y + PQ_z*PQ_z;\n";
    os << "\n";
    os << indent5 << cdbltype << " alpha = PQalpha_mul * one_over_PQalpha_sum;   // alpha from MEST\n";

    if(hasoneoverp)
        os << indent5 << cdbltype << " one_over_p = " << WriterInfo::NamedConstant("const_1") << " / P_alpha;\n";

    if(hasoneoverq)
        os << indent5 << cdbltype << " one_over_q = " << WriterInfo::NamedConstant("const_1") << " / Q_alpha;\n";

    if(hasoneover2p)    
        os << indent5 << cdbltype << " one_over_2p = " << WriterInfo::NamedConstant("one_half") << " * one_over_p;  // gets multiplied in VRR\n";

    if(hasoneover2q)    
        os << indent5 << cdbltype << " one_over_2q = " << WriterInfo::NamedConstant("one_half") << " * one_over_q;  // gets multiplied in VRR\n";

    if(hasoneover2pq)
        os << indent5 << cdbltype << " one_over_2pq = " << WriterInfo::NamedConstant("one_half") << " * one_over_PQalpha_sum;\n";

    if(hasketvrr)
    {
        if(WriterInfo::HasVRR_K())
        {
            os << indent5 << WriterInfo::NewConstDoubleLoad("Q_PA_x", "Q.PA_x", "j") << ";\n";
            os << indent5 << WriterInfo::NewConstDoubleLoad("Q_PA_y", "Q.PA_y", "j") << ";\n";
            os << indent5 << WriterInfo::NewConstDoubleLoad("Q_PA_z", "Q.PA_z", "j") << ";\n";
        }
        else
        {
            os << indent5 << WriterInfo::NewConstDoubleLoad("Q_PB_x", "Q.PB_x", "j") << ";\n";
            os << indent5 << WriterInfo::NewConstDoubleLoad("Q_PB_y", "Q.PB_y", "j") << ";\n";
            os << indent5 << WriterInfo::NewConstDoubleLoad("Q_PB_z", "Q.PB_z", "j") << ";\n";
        }
    }

    if(hasbravrr)
    {
        os << "\n";
        os << indent5 << "// NOTE: Minus sign!\n";
        os << indent5 << cdbltype << " a_over_p =  -alpha * one_over_p;     // a/p from MEST\n";
        os << indent5 << cdbltype << " aop_PQ_x = a_over_p * PQ_x;\n"; 
        os << indent5 << cdbltype << " aop_PQ_y = a_over_p * PQ_y;\n"; 
        os << indent5 << cdbltype << " aop_PQ_z = a_over_p * PQ_z;\n"; 
    }

    if(hasketvrr)
    {
        os << "\n";
        os << indent5 << "// NOTE: Minus sign\n";
        os << indent5 << "// NOTE2: Plus sign taken care of on aoq_PQ_x!\n";
        os << indent5 << cdbltype << " a_over_q =  -alpha * one_over_q;     // a/q from MEST\n";
        os << indent5 << cdbltype << " aoq_PQ_x = -a_over_q * PQ_x;\n"; 
        os << indent5 << cdbltype << " aoq_PQ_y = -a_over_q * PQ_y;\n"; 
        os << indent5 << cdbltype << " aoq_PQ_z = -a_over_q * PQ_z;\n"; 

    }

    if(hasketet || hasbraet)
    {
        os << indent5 << WriterInfo::NewConstDoubleLoad("Q_bAB_x", "Q.bAB_x", "j") << ";\n";
        os << indent5 << WriterInfo::NewConstDoubleLoad("Q_bAB_y", "Q.bAB_y", "j") << ";\n";
        os << indent5 << WriterInfo::NewConstDoubleLoad("Q_bAB_z", "Q.bAB_z", "j") << ";\n";
    }

    if(hasketet)
    {
        os << "\n";
        os << indent5 << cdbltype << " p_over_q = P_alpha * one_over_q;\n";
        os << indent5 << cdbltype << " etfac_k[3] = {\n";
        os << indent6 << "-(P_bAB_x + Q_bAB_x) * one_over_q,\n";
        os << indent6 << "-(P_bAB_y + Q_bAB_y) * one_over_q,\n";
        os << indent6 << "-(P_bAB_z + Q_bAB_z) * one_over_q,\n";
        os << indent6 << "};\n";
        os << "\n";
    }

    if(hasbraet)
    {
        os << "\n";
        os << indent5 << cdbltype << " q_over_p = Q_alpha * one_over_p;\n";
        os << indent5 << cdbltype << " etfac_b[3] = {\n";
        os << indent6 << "-(P_bAB_x + Q_bAB_x) * one_over_p,\n";
        os << indent6 << "-(P_bAB_y + Q_bAB_y) * one_over_p,\n";
        os << indent6 << "-(P_bAB_z + Q_bAB_z) * one_over_p,\n";
        os << indent6 << "};\n";
        os << "\n";
    }

    os << "\n";
    os << "\n";
    os << indent5 << "//////////////////////////////////////////////\n";
    os << indent5 << "// Boys function section\n";
    os << indent5 << "// Maximum v value: " << WriterInfo::L() << "\n";
    os << indent5 << "//////////////////////////////////////////////\n";
    os << indent5 << "// The paremeter to the boys function\n";
    os << indent5 << cdbltype << " F_x = R2 * alpha;\n";
    os << "\n";
    os << "\n";

    bg.WriteBoys(os);

    vrr_writer.WriteVRR(os);

    et_writer.WriteET(os);

    WriterInfo::WriteAccumulation(os);

        
    os << "\n";
    os << indent4 << "}  // close loop over j\n";
    os << indent3 << "}  // close loop over i\n";

    os << indent3 << "\n";
    os << indent3 << "//Advance to the next batch\n";
    os << indent3 << "jstart = SIMINT_SIMD_ROUND(jend);\n";
    if(!hashrr)
        os << indent3 << "abcd += nshellbatch;\n";
    os << indent3 << "\n";


    hrr_writer.WriteHRR(os);

    os << "\n";

    os << indent3 << "cd += nshellbatch;\n";

    os << indent2 << "}   // close loop cdbatch\n";

    os << "\n";
    os << indent2 << "istart = iend;\n";

    os << indent2 << "// if this is the end of a batch in the bra part, skip the padding\n";
    os << indent2 << "if( ((ab+1) % SIMINT_NSHELL_SIMD) == 0)\n";
    os << indent3 << "istart = SIMINT_SIMD_ROUND(istart);\n";
    os << "\n";

    os << indent1 << "}  // close loop over ab\n";
    os << "\n";
    os << "\n";

    os << "\n";

    WriterInfo::FreeContwork(os);

    os << indent1 << "return P.nshell12 * Q.nshell12;\n";
    os << "}\n";
    os << "\n";
}




