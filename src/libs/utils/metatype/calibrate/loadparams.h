#ifndef LOADPARAMS_H
#define LOADPARAMS_H

#define LOADPARAMS_POSIT_DIMENT         (3)
#define LOADPARAMS_ORIENT_DIMENT        (3)
#define LOADPARAMS_INERTIA_DIMENT       (3)
#include <cmath>

/// @brief Load Params Desc
typedef struct _LoadParams_
{
    _LoadParams_()
    {
        InitZero();
    }
    void InitZero()
    {
        Mass = 0;
        for (int i = 0; i < LOADPARAMS_POSIT_DIMENT; i++)
        {
            Cog[i] = 0;
            Orient[i] = 0;
            Inertia[i] = 0;
        }
    }
    _LoadParams_ &operator=(const _LoadParams_ &other)
    {
        this->Mass = other.Mass;
        for (int i = 0; i < LOADPARAMS_POSIT_DIMENT; i++)
        {
            this->Cog[i] = other.Cog[i];
            this->Orient[i] = other.Orient[i];
            this->Inertia[i] = other.Inertia[i];
        }
        return (*this);
    }
    bool operator==(const _LoadParams_ &other) const {
        return (fabs(this->Mass -other.Mass) < 0.000001) &&
               (fabs(this->Cog[0] - other.Cog[0]) < 0.000001) &&
               (fabs(this->Cog[1] - other.Cog[1]) < 0.000001) &&
               (fabs(this->Cog[2] - other.Cog[2]) < 0.000001) &&
               (fabs(this->Orient[0] - other.Orient[0]) < 0.000001) &&
               (fabs(this->Orient[1] - other.Orient[1]) < 0.000001) &&
               (fabs(this->Orient[2] - other.Orient[2]) < 0.000001) &&
               (fabs(this->Inertia[0] - other.Inertia[0]) < 0.000001) &&
               (fabs(this->Inertia[1] - other.Inertia[1]) < 0.000001) &&
               (fabs(this->Inertia[2] - other.Inertia[2]) < 0.000001);
    }
    double Mass;                                /// > mass
    double Cog[LOADPARAMS_POSIT_DIMENT];        /// > cogX cogY cogZ
    double Orient[LOADPARAMS_ORIENT_DIMENT];    /// > orientA orientB orientC
    double Inertia[LOADPARAMS_INERTIA_DIMENT];  /// > inertiaIX inertiaIY inertiaIZ
} LoadParams;

#endif  // LOADPARAMS_H
