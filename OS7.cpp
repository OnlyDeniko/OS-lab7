#include<bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    for(int i = 0;i < n;i++){
        int x;
        cin >> x;
    }
    vector<string> str(n);
    for(int i = 0;i < n;i++) cin >> str[i];
    queue<int> q;
    vector<int> ind(n, 0);
    vector<string> ans(n);
    set<int> in;

    q.push(0);
    in.insert(0);

    while(q.size()){
        int cur = q.front();
        q.pop();
        in.erase(cur);
        int ok = 1;
        set<int> added;
        vector<int> to_add;
        for(int i = 0;i < 2;i++){
            if (ind[cur] >= str[cur].size()){
                break;
            }
            if (str[cur][ind[cur]] == '-'){
                break;
            }

            for(int j = 0;j < n;j++){
                if (j == cur){
                    ans[cur].push_back('0');
                }
                else if (ind[j] >= str[j].size()) ans[j].push_back('x');
                else if (str[j][ind[j]] == '-') {
                    ans[j].push_back('-');
                    ind[j]++;
                }
                else if (str[j][ind[j]] == '0') {
                    ans[j].push_back('.');
                    to_add.push_back(j);
                }
            }
            ind[cur]++;
        }
        for(auto i : to_add){
            if (added.find(i) == added.end() && in.find(i) == in.end()) {
                q.push(i);
                in.insert(i);
                added.insert(i);
            }
        }

        if (q.size() == 0){
            for(int i = 0;i < n;i++){
                if (ind[i] < str[i].size() && str[i][ind[i]] == '0' && in.find(i) == in.end()) {
                    q.push(i);
                    in.insert(i);
                }
            }
        }
        while(q.size() == 0){
            int cnt = 0;
            for(int i = 0;i < n;i++){
                if (ind[i] >= str[i].size()) cnt++;
                if (ind[i] < str[i].size() && str[i][ind[i]] == '-') {
                    ans[i].push_back('-');
                    ind[i]++;
                }
                if (ind[i] < str[i].size() && str[i][ind[i]] == '0' && in.find(i) == in.end()) {
                    q.push(i);
                    in.insert(i);
                }
            }
            if (cnt == n) break;
        }
    }
    int ma = -1;
    for(auto i : ans) ma = max(ma, (int)i.size());
    for(auto &i : ans) while(i.size() < ma) i += 'x';

    for(auto i : ans) cout << i << '\n';

    cout << "Capacity: " << n << "/" << ma << '\n';
    string AroundTime = "(";
    for(int i = 0;i < n;i++){
        int gg = ma - 1;
        while(gg >= 0 && ans[i][gg] == 'x') gg--;
        AroundTime += to_string(gg + 1) + "+";
    }
    if (AroundTime.size() > 1) AroundTime.pop_back();
    AroundTime += ")/" + to_string(n);
    cout << "Around Time: " << AroundTime << '\n';
    int eff = 0;
    for(int i = 0;i < n;i++){
        eff += count(ans[i].begin(), ans[i].end(), '0');
    }
    cout << "Efficiency: " << eff << "/" << ma << '\n';
    int all_wait = 0;

    string waiting = "(";
    for(int i = 0;i < n;i++){
        int cnt = 0;
        int w8 = 0;
        for(int j = 0;j < ans[i].size();j++){
            if (ans[i][j] == '0'){
                if (w8){
                    all_wait++;
                    waiting += to_string(cnt) + "+";
                    w8 = cnt = 0;
                }
            } else {
                if (ans[i][j] == '-') w8++;
                if (ans[i][j] == '.' && w8) cnt++;
            }
        }
        if (w8){
            all_wait++;
            waiting += to_string(cnt) + "+";
            w8 = 0;
        }
    }
    if (waiting.size() > 1) waiting.pop_back();
    waiting += ")/" + to_string(all_wait);
    cout << "Waiting time: " << waiting << '\n';
    int cnt = 0;
    int now = 0;
    for(int i = 1;i < ma;i++){
        for(int j = 0;j < n;j++){
            if (ans[j][i] == '0' && now != j){
                cnt++;
                now = j;
            }
        }
    }
    cout << "Count switch: " << cnt << '\n';
    return 0;
}
