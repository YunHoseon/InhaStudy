#pragma once

class Scene;
class StartScene;
class LoadScene;
class GameScene;
class BattleScene;

enum class GameState;
enum class TimerID;

class SceneManager
{
public:
	HWND hWnd;

	Scene *curScene;
	StartScene *startScene;
	LoadScene *loadScene;
	GameScene *gameScene;
	BattleScene *battleScene;

	GameState gameState;
	TimerID timerId;

	SceneManager();
	virtual ~SceneManager();

	void ManagerInit();
	void ManagerUpdate(UINT message, WPARAM wParam, LPARAM lParam);
	void ManagerRender(HWND hWnd, HDC hdc);
	void SceneChange(GameState nextState);
};