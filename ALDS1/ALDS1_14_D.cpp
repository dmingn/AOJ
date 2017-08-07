#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

template<typename S_Iter, typename SA_Iter>
void induceSAL(S_Iter S_begin, S_Iter S_end, SA_Iter SA_begin, SA_Iter SA_end, const vector<bool> &t, uint32_t buckets_size) {
    int32_t n = S_end - S_begin;
    vector<int32_t> buckets(buckets_size+1, 0);
    for (auto itr = S_begin; itr != S_end; itr++) buckets[*itr]++;

    int32_t sum = 0;
    for (uint32_t i = 0; i < buckets.size(); i++) {
        sum += buckets[i];
        buckets[i] = sum - buckets[i];
    }

    if (!t[n-1]) SA_begin[buckets[S_begin[n-1]]++] = n-1;

    for (int32_t i = 0; i < n; i++) {
        if (SA_begin[i] > 0 && !t[SA_begin[i]-1]) SA_begin[buckets[S_begin[SA_begin[i]-1]]++] = SA_begin[i]-1;
    }

    return;
}

template<typename S_Iter, typename SA_Iter>
void induceSAS(S_Iter S_begin, S_Iter S_end, SA_Iter SA_begin, SA_Iter SA_end, const vector<bool> &t, uint32_t buckets_size) {
    int32_t n = S_end - S_begin;
    vector<int32_t> buckets(buckets_size+1, 0);
    for (auto itr = S_begin; itr != S_end; itr++) buckets[*itr]++;
    partial_sum(buckets.begin(), buckets.end(), buckets.begin());

    for (int32_t i = n-1; i > 0; i--) {
        if (SA_begin[i] > 0 && t[SA_begin[i]-1]) SA_begin[--buckets[S_begin[SA_begin[i]-1]]] = SA_begin[i]-1;
    }

    return;
}

template<typename S_Iter, typename SA_Iter>
void SA_IS(S_Iter S_begin, S_Iter S_end, SA_Iter SA_begin, SA_Iter SA_end, uint32_t buckets_size) {
    int32_t n = S_end - S_begin;
    fill(SA_begin, SA_end, -1);

    // classify the type of each character
    // true <=> S-type
    vector<bool> t(n);
    for (int32_t i = n; i >= 0; i--) {
        t[i] = S_begin[i] < S_begin[i+1] || (S_begin[i] == S_begin[i+1] && t[i+1]);
    }

    auto is_lms = [&t](int32_t i){return i > 0 && !t[i-1] && t[i];};

    // sort all the S-substrings
    vector<int32_t> buckets(buckets_size+1, 0);
    for (auto itr = S_begin; itr != S_end; itr++) buckets[*itr]++;
    partial_sum(buckets.begin(), buckets.end(), buckets.begin());
    for (int32_t i = 0; i < n; i++) {
        if (is_lms(i)) SA_begin[--buckets[S_begin[i]]] = i;
    }
    induceSAL(S_begin, S_end, SA_begin, SA_end, t, buckets_size);
    induceSAS(S_begin, S_end, SA_begin, SA_end, t, buckets_size);

    // compact all the sorted substrings into the first nl items of SA
    auto lms_end = remove_if(SA_begin, SA_end, [is_lms](int32_t x){return !is_lms(x);});
    fill(lms_end, SA_end, -1);
    int32_t nl = lms_end - SA_begin;

    // find the lexicographic names of substrings
    int32_t name = 0;
    for (auto itr = SA_begin; itr != lms_end; itr++) {
        if (itr == SA_begin) {
            lms_end[*itr/2] = name;
        } else {
            int32_t cur = *itr, prev = *(itr - 1);
            bool miss = S_begin[cur] != S_begin[prev] || t[cur] != t[prev];
            if (!miss) do {
                ++cur; ++prev;
                miss |= cur == n ||
                        prev == n ||
                        S_begin[cur] != S_begin[prev] ||
                        t[cur] != t[prev];
            } while (!miss && !(cur > 0 && !t[cur-1] && t[cur]) && !(prev > 0 && !t[prev-1] && t[prev]));

            if (miss) ++name;
            lms_end[*itr/2] = name;
        }
    }
    remove_if(reverse_iterator<decltype(SA_end)>(SA_end), reverse_iterator<decltype(SA_begin)>(SA_begin) - nl, [](int32_t i) {return i < 0;});

    // solve the reduced problem
    auto S1_begin = SA_end - nl, S1_end = SA_end;
    auto SA1_begin = SA_begin, SA1_end = SA_begin + nl;
    if (name + 1 < nl) {
        SA_IS(S1_begin, S1_end, SA1_begin, SA1_end, nl);
    } else {
        for (int32_t i = 0; i < nl; i++) {
            SA1_begin[S1_begin[i]] = i;
        }
    }

    // induce the result for the original problem
    fill(buckets.begin(), buckets.end(), 0);
    for (auto itr = S_begin; itr != S_end; itr++) buckets[*itr]++;
    partial_sum(buckets.begin(), buckets.end(), buckets.begin());

    for (int32_t i = 1, j = 0; i < n; i++) {
        if (is_lms(i)) S1_begin[j++] = i;
    }
    for (int32_t i = 0; i < nl; i++) SA1_begin[i] = S1_begin[SA1_begin[i]];
    fill(lms_end, SA_end, -1);
    for (int32_t i = nl-1; i >= 0; i--) {
        int32_t j = SA_begin[i];
        SA_begin[i] = -1;
        SA_begin[--buckets[S_begin[j]]] = j;
    }
    induceSAL(S_begin, S_end, SA_begin, SA_end, t, buckets_size);
    induceSAS(S_begin, S_end, SA_begin, SA_end, t, buckets_size);

    return;
}

int main() {
    char tmp[1000000];
    scanf("%s", tmp);
    string T = tmp;

    int32_t Q;
    scanf("%d", &Q);

    vector<int32_t> SA(T.length());
    SA_IS(T.begin(), T.end(), SA.begin(), SA.end(), 'z');

    for (int32_t i = 0; i < Q; i++) {
        char tmp[1000];
        scanf("%s", tmp);
        string P = tmp;

        auto itr_lb = lower_bound(SA.begin(), SA.end(), 0, [&T, &P](uint32_t i, uint32_t j) {return T.compare(i, T.length()-i, P) < 0;});

        if (*itr_lb <= T.length() - P.length() && T.substr(*itr_lb, P.length()) == P) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }

    return 0;
}
