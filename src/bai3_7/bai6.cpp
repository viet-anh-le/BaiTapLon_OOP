#include <bits/stdc++.h>
#include "Class.hpp"
using namespace std;

Pedestrian p;

void processEmotions(Pedestrian p, int H) {
	int lambda = p.personality.getLambda();
	vector<vector<double>> allEvents = p.getEvents();

	vector<vector<double>> allEmotions(6, vector<double>(1));
	allEmotions[0][0] = p.emotion.getPleasure();
	allEmotions[1][0] = p.emotion.getSurprise();
	allEmotions[2][0] = p.emotion.getAnger();
	allEmotions[3][0] = p.emotion.getFear();
	allEmotions[4][0] = p.emotion.getHate();
	allEmotions[5][0] = p.emotion.getSad();

	vector<int> when = {0};
	int lastTime = 0, index = 0;
	vector<double> temp(6, 0.0);
	double sum = 0;

	vector<int> times(19);
	uniform_int_distribution<int> time_distribution(4, 10);
	generate(times.begin(), times.end(), [&]() {
		return time_distribution(generator);
	});

	for (int i = 0; i < 6; i++)
		allEmotions[i].push_back(allEvents[i][0] + allEmotions[i][0] * exp(-lambda) + allEmotions[i][0]);

	for (int i = 2; i < H; i++) {
		for (int j = 0; j < 6; j++)
			temp[j] = allEmotions[j][i - 1];

		if (i - lastTime == times[index]) {
			index++;
			lastTime = i;
			sum = 0;

			for (int j = 0; j < 6; j++) sum += allEvents[j][index];

			when.push_back(i);

			for (int j = 0; j < 6; j++)
				temp[j] += allEmotions[j][i - 1] * exp(-lambda) + allEvents[j][index];
		}

		for (int j = 0; j < 6; j++)
			allEmotions[j].push_back(temp[j]);
	}

	ofstream fileOutput("allEmotions.txt");
	for (const auto& row : allEmotions) {
		for (double value : row)
			fileOutput << setprecision(2) << fixed << value << ' ';
		fileOutput << '\n';
	}
	fileOutput.close();
}

signed main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	Pedestrian p;
	processEmotions(p, floor(p.walkingTime));
}