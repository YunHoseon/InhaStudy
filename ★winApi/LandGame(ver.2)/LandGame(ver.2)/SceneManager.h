#pragma once

class Scene;			//클래스 전방선언
class StartScene;
class GameScene;
class EndScene;
enum class GameState;

class SceneManager
{
public:
	HWND hWnd;
	Scene *curScene;
	StartScene *startScene;
	GameScene *gameScene;
	EndScene *endScene;
	GameState gameState;

	SceneManager();
	~SceneManager();

	void ManagerInit();
	void ManagerUpdate(UINT message, WPARAM wParam, LPARAM lParam);
	void ManagerRender(HWND hWnd, HDC hdc);
	void SceneChange(GameState nextState);
};