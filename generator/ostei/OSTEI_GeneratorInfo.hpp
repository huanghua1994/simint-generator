#pragma once


#include "generator/Types.hpp"
#include "generator/GeneratorInfoBase.hpp"
#include "generator/Options.hpp"




class OSTEI_GeneratorInfo : public GeneratorInfoBase
{
public:    

    using GeneratorInfoBase::GeneratorInfoBase;

    //////////////////////////////////
    // Memory for contracted quartets
    //////////////////////////////////
    void SetContQ(const QAMSet & q)
    {
        contq_ = q;
        nelements_ = 0;
        for(const auto & it : contq_)
        {
            if(it != FinalAM())
                nelements_ += NCART(it.qam);
        }

        memory_ = nelements_ * sizeof(double);
    }

    QAMSet GetContQ(void) const
    {
        return contq_;
    }

    size_t ContMemoryReq(void) const
    {
        return memory_;
    }

    size_t ContNElements(void) const
    {
        return nelements_;
    }
    
    bool IsContQ(const QAM & am) const
    {
        return contq_.count(am);
    }

    bool IsUnique(void) const
    {
        QAM am = FinalAM();

        if(am[0] < am[1])
            return false;
        if(am[2] < am[3])
            return false;
        if( (am[0] + am[1]) < (am[2] + am[3]) )
            return false;
        if( (am[0] + am[1]) == (am[2] + am[3]) && (am[0] < am[2]) ) 
            return false;
        return true;
    }

private:
    //////////////////////////////////
    // Memory for contracted quartets
    //////////////////////////////////
    QAMSet contq_;
    size_t memory_;
    size_t nelements_;

};




