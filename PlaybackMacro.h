#ifndef PLAYBACKMACRO_H
#define PLAYBACKMACRO_H

class PlaybackMacro : public Macro
{
	public:
		PlaybackMacro(string);
		void loadMacro(string);
		void actionLoop();

};

#endif // !PLAYBACKMACRO_H


