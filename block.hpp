#ifndef BLOCK_HPP
#define BLOCK_HPP

#define BLOCKWIDTH 17
#define BLOCKHEIGHT 17

class Block {
    public:
        Block();
        void generate();
        void render(char **target);
        ~Block();
    private:
        char data[BLOCKHEIGHT][BLOCKWIDTH];
};

#endif
