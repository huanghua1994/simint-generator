/*! \file
 * 
 * \brief Base class for OSTEI Electron-transfer steps (header)
 * \author Benjamin Pritchard (ben@bennyp.org)
 */

#include <iostream>
#include <algorithm>
#include "generator/Printing.hpp"
#include "generator/ostei/OSTEI_ET_Algorithm_Base.hpp"


OSTEI_ET_Algorithm_Base::OSTEI_ET_Algorithm_Base(const OptionMap & options)
    : options_(options)
{
}


int OSTEI_ET_Algorithm_Base::GetOption(Option opt) const
{
    return options_.at(opt);
}

void OSTEI_ET_Algorithm_Base::PruneQuartets_(QuartetSet & qs, QuartetSet & pruned) const
{
    QuartetSet qsnew;

    // Prune anything from VRR
    for(auto & it : qs)
    {
        if(it)
        {
            if(direction_ == DoubletType::KET && it.ket.left.am() != 0)
                qsnew.insert(it);
            else if(direction_ == DoubletType::BRA && it.bra.left.am() != 0)
                qsnew.insert(it);
            else
                pruned.insert(it);
        }
    }

    qs = qsnew; 
}


void OSTEI_ET_Algorithm_Base::AMOrder_AddWithDependencies_(QAMList & order, QAM am) const
{
    // skip if it was already done somewhere
    if(std::find(order.begin(), order.end(), am) != order.end()) 
        return;

    // skip if it's not done by ET
    if(allam_.count(am) == 0)
        return;

    // get requirements
    QAMSet req = GetAMReq(am);

    for(const auto & it : req)
        AMOrder_AddWithDependencies_(order, it);

    order.push_back(am);
}


void OSTEI_ET_Algorithm_Base::ETStepLoop_(ETStepList & etsl,
                                   const QuartetSet & inittargets,
                                   QuartetSet & solvedquartets,
                                   QuartetSet & pruned)
{
    QuartetSet targets = inittargets;

    // steps, sorted by their am
    std::map<QAM, ETStepList> etslmap;

    while(targets.size())
    {
        QuartetSet newtargets;

        for(auto it = targets.begin(); it != targets.end(); ++it)
        {
            // skip if done already
            // this can happen with some of the more complex trees
            if(solvedquartets.count(*it) > 0)
                continue;

            ETStep ets = this->ETStep_(*it);

            // add to the list
            etsl.push_back(ets);

            for(const auto & it2 : ets.src)
            {
                if(it2 && solvedquartets.count(it2) == 0)
                    newtargets.insert(it2);
            }
       
            // insert copy with no flags 
            solvedquartets.insert(*it);
        }

        //cout << "Generated " << newtargets.size() << " new targets\n";
        //cout << "Before pruning: " << newtargets.size() << " new targets\n";
        //for(const auto & it : newtargets)
        //    std::cout << "    " << it << "\n";

        PruneQuartets_(newtargets, pruned);

        //cout << "After pruning: " << newtargets.size() << " new targets\n";
        //for(const auto & it : newtargets)
        //    std::cout << "    " << it << "\n";

        targets = newtargets;
    } 
}


void OSTEI_ET_Algorithm_Base::Create(QAM am, DoubletType direction)
{
    Create(GenerateInitialQuartetTargets(am), direction);
}


void OSTEI_ET_Algorithm_Base::Create(const QuartetSet & inittargets, DoubletType direction)
{
    direction_ = direction;

    // holds all the 'solved' quartets
    QuartetSet solvedquartets;

    // generate initial targets
    QuartetSet targets = inittargets;

    PruneQuartets_(targets, ettop_);
    PrintQuartetSet(targets, "Initial ET Targets");

    // Solve
    ETStepList etstep;
    ETStepLoop_(etstep, targets, solvedquartets, ettop_);


    std::cout << "\n\n";
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "ET step done. Solution is " << etsteps_.size() << " steps\n";
    std::cout << "--------------------------------------------------------------------------------\n";
    //for(auto & it : etsteps_)
    //    std::cout << it << "\n";

    std::cout << "\n\n";

    // store top level stuff
    for(const auto & it : ettop_)
        ettopam_.insert(it.amlist());

    // sort the step by AM and store the requirements
    for(const auto & it : etstep)
    {
        QAM qam = it.target.amlist();
        etsteps_[qam].push_back(it);

        for(const auto & it2 : it.src)
        {
            if(it2)
                etreq_[qam].insert(it2.amlist());
        }

        int stepidx = XYZStepToIdx(it.xyz);
        int ival, kval;

        if(direction_ == DoubletType::KET)
        {
            ival = it.target.bra.left.ijk[stepidx];
            kval = (it.target.ket.left.ijk[stepidx]-1);

            if(ival > 0)
            {
                intreq_[qam].insert(ival);
                allintreq_q_.insert(ival);
            }
            if(kval > 0)
            {
                intreq_[qam].insert(kval);
                allintreq_q_.insert(kval);
            }
        }
        else
        {
            ival = it.target.ket.left.ijk[stepidx];
            kval = (it.target.bra.left.ijk[stepidx]-1);

            if(ival > 0)
            {
                intreq_[qam].insert(ival);
                allintreq_p_.insert(ival);
            }
            if(kval > 0)
            {
                intreq_[qam].insert(kval);
                allintreq_p_.insert(kval);
            }
        }
    }

    // store all intreq
    for(const auto & it : intreq_)
        allintreq_.insert(it.second.begin(), it.second.end());

    // store all solved qam
    for(const auto & it : solvedquartets)
        allam_.insert(it.amlist());


    // determine the proper order to do these in
    for(const auto & q : inittargets)
        AMOrder_AddWithDependencies_(amorder_, q.amlist()); 

    PrintQuartetSet(ettop_, "Top level ET");
}


ETStepList OSTEI_ET_Algorithm_Base::GetSteps(QAM am) const
{
    return etsteps_.at(am);
}

QAMList OSTEI_ET_Algorithm_Base::GetAMOrder(void) const
{
    return amorder_;
}

QAMSet OSTEI_ET_Algorithm_Base::GetAllAM(void) const
{
    return allam_;
}

QAMSet OSTEI_ET_Algorithm_Base::GetAMReq(QAM am) const
{
    return etreq_.at(am);
}

QuartetSet OSTEI_ET_Algorithm_Base::TopQuartets(void) const
{
    return ettop_;
}

QAMSet OSTEI_ET_Algorithm_Base::TopAM(void) const
{
    return ettopam_;
}

IntSet OSTEI_ET_Algorithm_Base::GetIntReq(QAM am) const
{
    if(intreq_.count(am))
        return intreq_.at(am);
    else
        return IntSet();
}

DoubletType OSTEI_ET_Algorithm_Base::GetDirection(void) const
{
    return direction_;
}

IntSet OSTEI_ET_Algorithm_Base::GetAllInt(void) const
{
    return allintreq_;
}

IntSet OSTEI_ET_Algorithm_Base::GetAllInt_p(void) const
{
    return allintreq_p_;
}

IntSet OSTEI_ET_Algorithm_Base::GetAllInt_q(void) const
{
    return allintreq_q_;
}
        

bool OSTEI_ET_Algorithm_Base::HasET(void) const
{
    return HasBraET() || HasKetET();
}

bool OSTEI_ET_Algorithm_Base::HasBraET(void) const
{
    return (direction_ == DoubletType::BRA && allam_.size() > 0);
}


bool OSTEI_ET_Algorithm_Base::HasKetET(void) const
{
    return (direction_ == DoubletType::KET && allam_.size() > 0);
}

