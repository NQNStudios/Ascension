#pragma once

#include <memory>

#include "Input.h"
#include "Graphics.h"
#include "Screen.h"

///<summary>
/// Game class for The Fool's Revenge.
///</summary>
class Game
{
	public:
		///<summary>
		/// Creates and sets up the game.
		///</summary>
		Game();
		~Game();

		///<summary>
		/// Runs the game's event loop.
		///</summary>
		void Run();

		///<summary>
		/// Stops running the game's event loop and quits the game.
		///</summary>
		void Quit();
	private:
		///<summary>
		/// Loads all of the game's assets.
		///</summary>
		void LoadContent();

		///<summary>
		/// Handles the game's update logic.
		///</summary>
		void Update(int deltaMS);

		///<summary>
		/// Handles the game's input.
		///</summary>
		void HandleInput(ascii::Input& input);

		///<summary>
		/// Draws the game.
		///</summary>
		void Draw(ascii::Graphics& graphics);

		bool mRunning;

		std::unique_ptr<Screen> mScreen;
};

