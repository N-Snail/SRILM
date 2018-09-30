/*
 * NBest.h --
 *	N-best lists
 *
 * Copyright (c) 1995-2000, SRI International.  All Rights Reserved.
 *
 * @(#)$Header: /home/srilm/devel/lm/src/RCS/NBest.h,v 1.21 2000/05/10 00:24:58 stolcke Exp $
 *
 */

#ifndef _NBest_h_
#define _NBest_h_

#include <iostream.h>

#include "Boolean.h"
#include "Prob.h"
#include "File.h"
#include "Vocab.h"
#include "Array.h"
#include "LM.h"
#include "MemStats.h"
#include "Debug.h"

/* 
 * Magic string headers identifying Decipher N-best lists
 */
const char nbest1Magic[] = "NBestList1.0";
const char nbest2Magic[] = "NBestList2.0";

/*
 * A hypothesis in an N-best list with associated info
 */
class NBestHyp {
public:
    NBestHyp();
    ~NBestHyp();
    NBestHyp &operator= (const NBestHyp &other);

    void rescore(LM &lm, double lmScale, double wtScale);
    void decipherFix(LM &lm, double lmScale, double wtScale);
    void reweight(double lmScale, double wtScale, double amScale = 1.0);

    Boolean parse(char *line, Vocab &vocab, unsigned decipherFormat = 0,
			LogP acousticOffset = 0.0, Boolean multiwords = false);
    void write(File &file, Vocab &vocab, Boolean decipherFormat = true,
						    LogP acousticOffset = 0.0);

    VocabIndex *words;
    LogP acousticScore;
    LogP languageScore;
    unsigned numWords;
    LogP totalScore;
    Prob posterior;
    unsigned numErrors;
};

class NBestList: public Debug
{
public:
    NBestList(Vocab &vocab, unsigned maxSize = 0, Boolean multiwords = false);
    ~NBestList() {};

    static unsigned initialSize;

    unsigned numHyps() { return _numHyps; };
    NBestHyp &getHyp(unsigned number) { return hypList[number]; };
    void sortHyps();

    void rescoreHyps(LM &lm, double lmScale, double wtScale);
    void decipherFix(LM &lm, double lmScale, double wtScale);
    void reweightHyps(double lmScale, double wtScale, double amScale = 1.0);
    void computePosteriors(double lmScale, double wtScale,
					double postScale, double amScale = 1.0);
    void removeNoise(LM &lm);

    unsigned wordError(const VocabIndex *words,
				unsigned &sub, unsigned &ins, unsigned &del);

    double minimizeWordError(VocabIndex *words, unsigned length,
				double &subs, double &inss, double &dels,
				unsigned maxRescore = 0, Prob postPrune = 0.0);

    void acousticNorm();
    void acousticDenorm();

    Boolean read(File &file);
    Boolean write(File &file, Boolean decipherFormat = true,
						unsigned numHyps = 0);
    void memStats(MemStats &stats);

    Vocab &vocab;
    LogP acousticOffset;

private:
    Array<NBestHyp> hypList;
    unsigned _numHyps;
    unsigned maxSize;
    Boolean multiwords;
};

#endif /* _NBest_h_ */
