//1. For github, if not commiting but just adding, the files would be merged/mixed. It's understood as once modifying twice the file, either of previous version can be got back.
//   Otherwise, by committing the files, every phase can be saved up in the time line like history and can be recovered by git_init.
//   However git_diff shows the change unstaged but no way to distinguish les parts amid the staged. 
//2. Add means adding sth to be staged => but the files never tracked. Thus git_add play a role in tracking a new file and stage every change of it!!!  only temporary.

#include "Curve.h"

// Function body for IRCurve Class
IRCurve::IRCurve(vCurve _irVector):
		irVector(_irVector){}


double IRCurve::GetParam(const double time) const //A constant iterator is a container for access only, and cannot be used to modify the associated variable.
{
	aNoeud noeudCurrent, noeudClosest = irVector.at(0);
	double dCurrent, dClosest = std::abs(noeudClosest[0]-time);
	
	double irCurrent, irClosest = noeudClosest[1];

	//for (vCurve::const_iterator it = irVector.begin(); it != irVector.end(); it++)
	for (int i = 0; i < irVector.size(); i++)
	{
		noeudCurrent = irVector.at(i);
		dCurrent = std::abs(noeudCurrent[0]-time);
		irCurrent = noeudCurrent[1];
		if (dCurrent < dClosest) { noeudClosest = noeudCurrent; dClosest = dCurrent; irClosest = irCurrent; }
	}
	return irClosest;
}


// Function body for VolCurve Class
VolCurve::VolCurve(vCurve _irVector):
		volVector(_irVector){}


double VolCurve::GetParam(const double time) const //A constant iterator is a container for access only, and cannot be used to modify the associated variable.
{
	aNoeud noeudCurrent, noeudClosest = volVector.at(0);
	double dCurrent, dClosest = std::abs(noeudClosest[0]-time);
	
	double volCurrent, volClosest = noeudClosest[1];

	//for (vCurve::const_iterator it = irVector.begin(); it != irVector.end(); it++)
	for (int i = 0; i < volVector.size(); i++)
	{
		noeudCurrent = volVector.at(i);
		dCurrent = std::abs(noeudCurrent[0]-time);
		volCurrent = noeudCurrent[1];
		if (dCurrent < dClosest) { noeudClosest = noeudCurrent; dClosest = dCurrent; volClosest = volCurrent; }
	}
	return volClosest;
}
