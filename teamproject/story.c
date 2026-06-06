#include "story.h"

char startStory[][100] = {
	"시작",
	"스토리",
	"입니다",
};

const int startStoryCount = sizeof(startStory) / sizeof(startStory[0]);

char easyStory[][100] = {
	"난이도 1",
	"스토리",
	"입니다."
};

const int easyStoryCount = sizeof(easyStory) / sizeof(easyStory[0]);

char normalStory[][100] = {
	"난이도 2",
	"스토리",
	"입니다."
};

const int normalStoryCount = sizeof(normalStory) / sizeof(normalStory[0]);

char hardStory[][100] = {
	"난이도 3",
	"스토리",
	"입니다."
};

const int hardStoryCount = sizeof(hardStory) / sizeof(hardStory[0]);