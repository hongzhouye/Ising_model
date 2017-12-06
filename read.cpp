#include "include/read.hpp"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <functional>


void removeSpace (vs& spline)
{
	vs spline_new;
	for (auto it = spline.begin (); it != spline.end (); ++it)
		if (*it != "")	spline_new.push_back (*it);
	spline = spline_new;
}


/* These two functions split a string with given delimeter */
void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
//  remove extra spaces
    removeSpace (elems);
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);

//  remove extra spaces in elems and
//  store the resulting vs in elems_new.
    vs elems_new;
    for (auto it = elems.begin (); it != elems.end (); ++it)
	{
		vs temp;  split(*it, ' ', temp);
		elems_new.insert (elems_new.end (), temp.begin (), temp.end ());
	}

    return elems_new;
}


/* This function turns a string into all uppercase */
string uppercase(const string& s)
{
	string result (s.length (), ' ');
	transform (
			s.begin (),
			s.end (),
			result.begin (),
			ptr_fun <int, int> (toupper)
			);
	return result;
}


/* split a string like
 *      "N = 5" or "N=5" or "N= 5" or "N =5"
 * into a vector<string> with elements "N" and "5"
 */
vs split_eq(string line)
{
    return split(line, '=');
}


void read_param(PARAM* p, const string& fname)
{
    string line;
    ifstream input (fname);
    if (input)	// same as: if (input.good ())
    {
		cout << "  ** Input **" << endl;
        while (getline (input, line))	// same as ".good ()"
        {
            if (line.empty () || line[0] == '#')    continue;

			cout << "    " << line << endl;

            vs spline = split_eq(line);
            if (uppercase(spline[0]) == "L")
                p->L = (int) stod(spline[1]);
            else if (uppercase(spline[0]) == "T")
                p->T = stod (spline[1]);
            else if (uppercase(spline[0]) == "H")
                p->H = stod (spline[1]);
            else if (uppercase(spline[0]) == "MAXSTEP")
                p->MaxStep = (int) stod(spline[1]);
            else if (uppercase(spline[0]) == "AVESTEP")
                p->AveStep = (int) stod(spline[1]);
            else if (uppercase(spline[0]) == "INIT_LAT_TYPE")
                p->init_lat_type = (int) stod(spline[1]);
            else if (uppercase(spline[0]) == "M_AVE")
                p->iM_ave = (uppercase(spline[1]) == "TRUE") ?
                    (true) : (false);
            else if (uppercase(spline[0]) == "X_AVE")
                p->iX_ave = (uppercase(spline[1]) == "TRUE") ?
                    (true) : (false);
            else if (uppercase(spline[0]) == "WRITE_TRAJ")
                p->iwrite_traj = (uppercase(spline[1]) == "TRUE") ?
                    (true) : (false);
            else if (uppercase(spline[0]) == "WRITE_TO")
                p->write_to = spline[1];
            else if (uppercase(spline[0]) == "WRITE_FREQ")
                p->write_freq = (int) stod(spline[1]);
            else
            {
                cout << "[ERROR] unknown option \"" << spline[0] <<"\" in "
                    << fname << endl;
                exit (1);
            }
        }
        input.close ();
        cout << "  ** End input **" << endl << endl;
    }
    else
    {
        cout << "[ERROR] invalid job control file: " << fname << endl;
        exit (1);
    }
}
