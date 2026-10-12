#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

struct Interval {
    int l, r;
    bool operator<(const Interval& other) const {
        return l < other.l || (l == other.l && r < other.r);
    }
};

class AttendanceSystem {
private:
    set<Interval> activities; // Skipping activities
    
public:
    // Add activity [l,r] and remove all conflicting activities
    // Return number of deleted activities
    int addActivity(int l, int r) {
        int deleted_count = 0;
        
        // Find the first activity that could overlap with [l,r]
        auto it = activities.lower_bound({l, r});
        
        // Check the activity before the found position
        vector<Interval> to_delete;
        
        // Check previous activity
        if (it != activities.begin()) {
            auto prev_it = it;
            --prev_it;
            if (prev_it->r >= l) { // Overlaps with [l,r]
                to_delete.push_back(*prev_it);
            }
        }
        
        // Check current and subsequent activities
        while (it != activities.end() && it->l <= r) {
            if (it->r >= l) { // Overlaps with [l,r]
                to_delete.push_back(*it);
            }
            ++it;
        }
        
        // Delete all overlapping activities
        for (const auto& interval : to_delete) {
            activities.erase(interval);
            deleted_count++;
        }
        
        // Add the new activity
        activities.insert({l, r});
        
        return deleted_count;
    }
    
    // Return current count of available activities
    int getAvailableCount() const {
        return activities.size();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    AttendanceSystem system;
    
    for (int i = 0; i < n; i++) {
        char op;
        cin >> op;
        
        if (op == 'A') {
            int l, r;
            cin >> l >> r;
            cout << system.addActivity(l, r) << "\n";
        } else if (op == 'B') {
            cout << system.getAvailableCount() << "\n";
        }
    }
    
    return 0;
}