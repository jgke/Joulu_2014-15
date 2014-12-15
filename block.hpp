#ifndef BLOCK_HPP
#define BLOCK_HPP

#define BLOCKWIDTH 17
#define BLOCKHEIGHT 17
#define GENDISTANCE 6

class Block {
    public:
        Block();
        Block(int x, int y);
        void generate(Block neighbor[4]);
        void render(char **target);
        ~Block();
    private:
        char data[BLOCKHEIGHT][BLOCKWIDTH];
        int origx, origy;
};

#endif
