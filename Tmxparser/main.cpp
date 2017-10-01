#include <iostream>
#include "dependencies\include\TMXParser.h"
#include "dependencies\include\TSXParser.h"
#include <SDL.h>
#include "Tile.h"
#include <regex>

using namespace std;

void Render(SDL_Renderer* renderer, SDL_Texture* texture, TMX::Parser tmx)
{
	SDL_RenderClear(renderer);

	char tileID = 0;

	const int tileWidth = tmx.mapInfo.tileWidth;
	const int tileHeight = tmx.mapInfo.tileHeight;
	//const int width = tmx.mapInfo.width;
	//const int height = tmx.mapInfo.height;
	Tile** tiles [30][20];
	for (std::map<std::string, TMX::Parser::TileLayer>::iterator it = tmx.tileLayer.begin(); it != tmx.tileLayer.end(); ++it) {
 		const char* content = tmx.tileLayer[it->first].data.contents.c_str();
		int i, j, k = 0;
		const regex number("[[:digit:]]");
		char* id = "";
		while (true)
		{						
			cout << content << endl;
			if (regex_match(content++, number))
			{
				id += content[k];
				k++;
				break;
			}
			k++;
		}


		for (int i = 0; i < tmx.mapInfo.width; i++)
		{
			for (int j = 0; j < tmx.mapInfo.height; j++)
			{
				//regex integer
				tileID = tmx.tileLayer[it->first].data.contents[k];
				k++;
				cout << tileID;
			}
			cout << endl;
		}
	}
}

void RenderTilesText(TMX::Parser tmx)
{
	for (std::map<std::string, TMX::Parser::TileLayer>::iterator it = tmx.tileLayer.begin(); it != tmx.tileLayer.end(); ++it) {
		std::cout << std::endl;
		std::cout << "Tile Layer Name: " << it->first << std::endl;
		std::cout << "Tile Layer Visibility: " << tmx.tileLayer[it->first].visible << std::endl;
		std::cout << "Tile Layer Opacity: " << tmx.tileLayer[it->first].opacity << std::endl;
		std::cout << "Tile Layer Properties:" << std::endl;
		if (tmx.tileLayer[it->first].property.size() != 0) {
			for (std::map<std::string, std::string>::iterator it2 = tmx.tileLayer[it->first].property.begin(); it2 != tmx.tileLayer[it->first].property.end(); ++it2) {
				std::cout << "-> " << it2->first << " : " << it2->second << std::endl;
			}
		}
		std::cout << "Tile Layer Data Encoding: " << tmx.tileLayer[it->first].data.encoding << std::endl;
		if (tmx.tileLayer[it->first].data.compression != "none") {
			std::cout << "Tile Layer Data Compression: " << tmx.tileLayer[it->first].data.compression << std::endl;
		}
		std::cout << "Tile Layer Data Contents: " << tmx.tileLayer[it->first].data.contents << std::endl;
	}
}

int main(int argc, char* argv[])
{
	cout << "Hello world!" << endl;
	TMX::Parser tmx;

	tmx.load("naamloos.tmx");

	//std::cout << "Map Version: " << tmx.mapInfo.version << std::endl;
	//std::cout << "Map Orientation: " << tmx.mapInfo.orientation << std::endl;
	//std::cout << "Map Width: " << tmx.mapInfo.width << std::endl;
	//std::cout << "Map Height: " << tmx.mapInfo.height << std::endl;
	//std::cout << "Tile Width: " << tmx.mapInfo.tileWidth << std::endl;
	//std::cout << "Tile Height: " << tmx.mapInfo.tileHeight << std::endl;
	//std::cout << "Background Color: " << tmx.mapInfo.backgroundColor << std::endl;
	//std::cout << "Properties: " << std::endl;
	//for (std::map<std::string, std::string>::iterator it = tmx.mapInfo.property.begin(); it != tmx.mapInfo.property.end(); ++it) {
	//	std::cout << "-> " << it->first << " : " << it->second << std::endl;
	//}
	RenderTilesText(tmx);
	/*
	for (std::map<std::string, TMX::Parser::ObjectGroup>::iterator it = tmx.objectGroup.begin(); it != tmx.objectGroup.end(); ++it) {
		std::cout << std::endl;
		std::cout << "Object Group Name: " << it->first << std::endl;
		std::cout << "Object Group Color: " << tmx.objectGroup[it->first].color << std::endl;
		std::cout << "Object Group Visibility: " << tmx.objectGroup[it->first].visible << std::endl;
		std::cout << "Object Group Opacity: " << tmx.objectGroup[it->first].opacity << std::endl;
		std::cout << "Object Group Properties:" << std::endl;
		if (tmx.objectGroup[it->first].property.size() != 0) {
			for (std::map<std::string, std::string>::iterator it2 = tmx.objectGroup[it->first].property.begin(); it2 != tmx.objectGroup[it->first].property.end(); ++it2) {
				std::cout << "-> " << it2->first << " : " << it2->second << std::endl;
			}
		}
		for (std::map<std::string, TMX::Parser::Object>::iterator it2 = tmx.objectGroup[it->first].object.begin(); it2 != tmx.objectGroup[it->first].object.end(); ++it2) {
			std::cout << std::endl;
			if (it2->second.name != "") { std::cout << "Object Name: " << it2->first << std::endl; }
			if (it2->second.type != "") { std::cout << "Object Type: " << tmx.objectGroup[it->first].object[it2->first].type << std::endl; }
			std::cout << "Object Position X: " << tmx.objectGroup[it->first].object[it2->first].x << std::endl;
			std::cout << "Object Position Y: " << tmx.objectGroup[it->first].object[it2->first].y << std::endl;
			std::cout << "Object Width: " << tmx.objectGroup[it->first].object[it2->first].width << std::endl;
			std::cout << "Object Height: " << tmx.objectGroup[it->first].object[it2->first].height << std::endl;
			if (it2->second.gid != 0) { std::cout << "Object Tile GID: " << tmx.objectGroup[it->first].object[it2->first].gid << std::endl; }
			std::cout << "Object Visible: " << tmx.objectGroup[it->first].object[it2->first].visible << std::endl;
		}
	}

	for (std::map<std::string, TMX::Parser::ImageLayer>::iterator it = tmx.imageLayer.begin(); it != tmx.imageLayer.end(); ++it) {
		std::cout << std::endl;
		std::cout << "Image Layer Name: " << it->first << std::endl;
		std::cout << "Image Layer Visibility: " << tmx.imageLayer[it->first].visible << std::endl;
		std::cout << "Image Layer Opacity: " << tmx.imageLayer[it->first].opacity << std::endl;
		std::cout << "Image Layer Properties:" << std::endl;
		if (tmx.imageLayer[it->first].property.size() != 0) {
			for (std::map<std::string, std::string>::iterator it2 = tmx.imageLayer[it->first].property.begin(); it2 != tmx.imageLayer[it->first].property.end(); ++it2) {
				std::cout << "-> " << it2->first << " : " << it2->second << std::endl;
			}
		}
		std::cout << "Image Layer Source: " << tmx.imageLayer[it->first].image.source << std::endl;
		std::cout << "Image Layer Transparent Color: " << tmx.imageLayer[it->first].image.transparencyColor << std::endl;
	}*/


	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		cout << SDL_GetError() << endl;

	SDL_Window* window = SDL_CreateWindow("TMX", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Texture* map = nullptr;
	//if (!(map = RenderMap(tmxMap)))
	//	cout << SDL_GetError() << endl;

	Render(renderer, map, tmx);

	SDL_Event e;
	while (SDL_WaitEvent(&e)) {
		if (e.type == SDL_QUIT) break;
		SDL_RenderClear(renderer);

	}
	return 0;
}