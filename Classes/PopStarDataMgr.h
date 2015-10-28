#ifndef __POPSTAR_DATA_MGR_H__
#define __POPSTAR_DATA_MGR_H__

class PopStarDataMgr
{
public:
	PopStarDataMgr();
	~PopStarDataMgr();

	bool init();

	int  getScore();
	void setScore(int score); // ���õ�ǰ����

	int  getLevel();
	void setLevel(int level);

	int  getHistoryScore();
	void setHistoryScore(int score);

	int  getHistoryLevelScoreByLevel(int level);
	void setHistoryLevelScore(int level, int score);

	int  getScoreByReduceNum(int num);		// ����������������ȡ�õ�����
	int  getScoreByLeftNum(int num);		// ����ʣ����������ȡ�õ�����
	int  getTargetScoreByLevel(int level);	// ���ݹؿ���ȡĿ�����

private:
	std::map<int, int> reduceNumScoreMap;
	std::map<int, int> leftNumScoreMap;

	int			curScore;
	int			gameLevel;
	int			historyScore;		// ��ʷ��߷�

	std::vector<int> historyLevelScores;
};

PopStarDataMgr& getPopStarDataMgr();

#endif // __POPSTAR_DATA_MGR_H__
