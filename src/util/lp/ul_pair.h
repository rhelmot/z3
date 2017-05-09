/*
  Copyright (c) 2017 Microsoft Corporation
  Author: Lev Nachmanson
*/

#pragma once
#include "util/vector.h"
#include <string>
#include <algorithm>
#include <utility>
#include "util/lp/column_info.h"

namespace lean {

    enum lconstraint_kind {
        LE = -2, LT = -1 , GE = 2, GT = 1, EQ = 0
    };
    
    inline std::ostream& operator<<(std::ostream& out, lconstraint_kind k) {
        switch (k) {
        case LE: return out << "<=";
        case LT: return out << "<";
        case GE: return out << ">=";
        case GT: return out << ">";
        case EQ: return out << "=";
        }
        return out << "??";
    }

inline bool compare(const std::pair<mpq, var_index> & a, const std::pair<mpq, var_index> & b) {
    return a.second < b.second;
}

class ul_pair {
    constraint_index m_low_bound_witness = static_cast<constraint_index>(-1);
    constraint_index m_upper_bound_witness = static_cast<constraint_index>(-1);
public:
    constraint_index& low_bound_witness() {return m_low_bound_witness;}
    constraint_index low_bound_witness() const {return m_low_bound_witness;}
    constraint_index& upper_bound_witness() { return m_upper_bound_witness;}
    constraint_index upper_bound_witness() const {return m_upper_bound_witness;}
    row_index m_i = static_cast<row_index>(-1);
    bool operator!=(const ul_pair & p) const {
        return !(*this == p);
    }

    bool operator==(const ul_pair & p) const {
        return m_low_bound_witness == p.m_low_bound_witness
            && m_upper_bound_witness == p.m_upper_bound_witness &&
            m_i == p.m_i;
    }
	// empty constructor
	ul_pair(){}
    ul_pair(row_index ri) : m_i(ri) {}
    ul_pair(const ul_pair & o): m_low_bound_witness(o.m_low_bound_witness), m_upper_bound_witness(o.m_upper_bound_witness), m_i(o.m_i) {}
};

}
