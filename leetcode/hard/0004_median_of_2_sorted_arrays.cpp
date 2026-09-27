class Solution {
private:
    double _find_from_nums2(vector<int>& nums1, vector<int>& nums2, int l1, int r1, int low, int up, int mid) {
        // cout << "OK1\n";
        mid -= l1 + 1;
        // cout << mid << " OK2\n";
        if (mid <= low) {
            // cout << "OK3\n";
            return double(nums1[l1]);
        }
        else if (mid >= up) {
            // cout << "OK4\n";
            return double(nums1[r1]);
        }
        // cout << "OK5\n";
        return double(nums2[mid]);
    }
    double _compute_up_low_and_median(vector<int>& nums1, vector<int>& nums2, int l1, int r1) {
        int m = nums1.size(), n = nums2.size();
        int low=-1, up=n; // Positions in nums2.
        if (l1 >= 0) {
            low = lower_bound(nums2.begin(), nums2.end(), nums1[l1]) - nums2.begin();
        }
        if (low >= 0 && nums2[low] >= nums1[l1]) {low--;}
        if (r1 < m) {
            up = upper_bound(nums2.begin(), nums2.end(), nums1[r1]) - nums2.begin();
        }
        // cout << low << ";" << up;
        int mid1 = (n+m-1)/2, mid2 = (n+m)/2;
        double d1 = _find_from_nums2(nums1, nums2, l1, r1, low, up, mid1);
        double d2 = _find_from_nums2(nums1, nums2, l1, r1, low, up, mid2);
        return (d1 + d2)/2.;
    }

public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        if (n == 0) {
            if (m % 2 == 1) {return double(nums1[m/2]);}
            else {return (double(nums1[m/2]) + double(nums1[m/2-1]))/2;}
        }
        else if(m == 0) {
            if (n % 2 == 1) {return double(nums2[n/2]);}
            else {return (double(nums2[n/2]) + double(nums2[n/2-1]))/2;}
        }
        int l1=-1, l2=-1, r1=m, r2=n;
        while (r1-l1>1 && r2-l2>1) {
            // cout << "(" << l1 << "," << r1 << "), (" << l2 << ", " << r2 << ")\n";
            int mid1 = (l1+r1)/2, mid2 = (l2+r2)/2; // Mid or lower, depends of parity.
            if (nums1[mid1] < nums2[mid2]) {
                if (mid1+mid2+2 < m-mid1 + n-mid2) {l1 = mid1;}
                else {r2=mid2;}
            }
            else {
                if (mid1+mid2+2 < m-mid1 + n-mid2) {l2 = mid2;}
                else {r1=mid1;}
            }
        }
        // cout << "(" << l1 << "," << r1 << "), (" << l2 << ", " << r2 << ")\n";
        if (r1-l1 <= 1) {
            return _compute_up_low_and_median(nums1, nums2, l1, r1);
        }
        // r2-l2 = 1
        return _compute_up_low_and_median(nums2, nums1, l2, r2);
    }
};
