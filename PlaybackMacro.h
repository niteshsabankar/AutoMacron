#ifndef PLAYBACKMACRO_H
#define PLAYBACKMACRO_H

class PlaybackMacro : public Macro
{
	public:
		void loadMacro(string);
		void actionLoop(vector<int>);

};

#endif // !PLAYBACKMACRO_H

