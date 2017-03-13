#ifndef MAZE_H_INCL
#define MAZE_H_INCL

#include<cstddef>

/**
 * Provides functionality required to model a maze. A maze is a grid of cells,
 * each marks accessibility between them. It can be seen as a potentially
 * disconnected bidirected 2d lattice graph.
 */
namespace maze {
    /**
     * Type alias used for indexes inside the maze.
     */
    typedef std::size_t index;

    /**
     * A single cell in a maze. It models both the data stored in the cell and
     * the legal exits of the cell.
     */
    template <typename T> class RawCell {
    public:
        /**
         * A type alias for the stored type.
         */
        typedef T type;

        /**
         * Creates a new RawCell<type> with no exits.
         */
        RawCell(type data) {
            *this = RawCell(data, false, false, false, false);
        }

        /**
         * Creates a new RawCell<type> with specified exits.
         */
        RawCell(type data, bool north, bool east, bool south, bool west) {
            this->data = data;
            this->north = north;
            this->east = east;
            this->south = south;
            this->west = west;
        }

        /**
         * The data stored inside the cell.
         */
        type data;

        /**
         * Legal to exit to the north.
         */
        bool north;

        /**
         * Legal to exit to the east.
         */
        bool east;

        /**
         * Legal to exit to the south.
         */
        bool south;

        /**
         * Legal to exit to the west.
         */
        bool west;
        /**@}*/
    };

    /**
     * A safe wrapper around a pointer to a RawCell. Provides getter and setter
     * methods. Cell is invalidated if Maze goes out of scope.
     */
    template <typename T> class Cell {
    public:
        /**
         * A type alias for the stored type.
         */
        typedef T type;

        /**
         * Constructs a new wrapper around a cell, from a RawCell, its position, and
         * its bounds. The RawCell should be the RawCell being Wrapped, not the
         * RawCell at the start of the Maze's memory.
         */
        Cell(RawCell<type>* cell, index pos_x, index pos_y, index bound_x,
             index bound_y) {
            this->cell = cell;
            this->pos_x = pos_x;
            this->pos_y = pos_y;
            this->bound_x = bound_x;
            this->bound_y = bound_y;
        }

        /**
         * Returns a pointer to the data stored in the cell.
         */
        type* data() {
            return this->cell.data;
        }

        /**
         * Checks if the target Cell is a null pointer.
         */
        bool is_null() {
            return this->cell == (void*)0;
        }

        /**
         * Getter method for pos_x.
         */
        index get_pos_x() {
            return this->pos_x;
        }

        /**
         * Getter method for pos_y.
         */
        index get_pos_y() {
            return this->pos_y;
        }

        /**
         * Getter method for bound_x.
         */
        index get_bound_x() {
            return this->bound_x;
        }

        /**
         * Getter method for bound_y.
         */
        index get_bound_y() {
            return this->bound_y;
        }

        /**
         * Getter method for north. Returns false if out of bounds, regardless of
         * underlying value.
         */
        bool get_north();

        /**
         * Getter method for east. Returns false if out of bounds, regardless of
         * underlying value.
         */
        bool get_east();

        /**
         * Getter method for south. Returns false if out of bounds, regardless of underlying value.
         */
        bool get_south();

        /**
         * Getter method for west. Returns false if out of bounds, regardless of underlying value.
         */
        bool get_west();

        /**
         * Setter method for north. Returns false if out of bounds.
         */
        bool set_north(bool);

        /**
         * Setter method for east. Returns false if out of bounds.
         */
        bool set_east(bool);

        /**
         * Setter method for south. Returns false if out of bounds.
         */
        bool set_south(bool);

        /**
         * Setter method for west. Returns false if out of bounds.
         */
        bool set_west(bool);

        /**
         * Returns the north adjacent Cell. Target RawCell will be null if done
         * at a boundry.
         */
        Cell at_north();

        /**
         * Returns the east adjacent Cell. Target RawCell will be null if done
         * at a boundry.
         */
        Cell at_east();

        /**
         * Returns the south adjacent Cell. Target RawCell will be null if done
         * at a boundry.
         */
        Cell at_south();

        /**
         * Returns the west adjacent Cell. Target RawCell will be null if done
         * at a boundry.
         */
        Cell at_west();

        /**
         * Mutates cell in place to be its north neighbour. Returns false and
         * does not change if at a boundry.
         */
        bool to_north();

        /**
         * Mutates cell in place to be its east neighbour. Returns false and
         * does not change if at a boundry.
         */
        bool to_east();

        /**
         * Mutates cell in place to be its south neighbour. Returns false and
         * does not change if at a boundry.
         */
        bool to_south();

        /**
         * Mutates cell in place to be its west neighbour. Returns false and
         * does not change if at a boundry.
         */
        bool to_west();

    protected:
        /**
         * The underlying RawCell.
         */
        RawCell<type>* cell;

        /**
         * The x position in the maze.
         */
        index pos_x;
        /**
         * The y position in the maze.
         */
        index pos_y;

        /**
         * The x boundry of the maze.
         */
        index bound_x;
        /**
         * The y boundry of the maze.
         */
        index bound_y;
    };

    /**
     * A maze. Stores size, and controls memory of elements. A maze can be seen
     * as a potentially disconnected bidirected 2d lattice graph.
     */
    template <typename T> class Maze {
    public:
        /**
         * A type alias for the stored type.
         */
        typedef T type;

        /**
         * Creates a new Maze from size. Allocates memory and initalizes fully
         * blocked cells.
         */
        Maze(index size_x, index size_y);

        /**
         * Creates a new Maze from size and a template. Allocates memory and
         * initalizes fully with coppies of a supplied cell.
         */
        Maze(index size_x, index size_y, RawCell<type> init);

        /**
         * Creates a Maze from its raw parts. Takes "ownership" of `cells` and
         * will deallocate it when it's destructor is called.
         */
        Maze(RawCell<type>* cell, index size_x, index size_y);

        /**
         * Deallocates the memory reserved for the cells of the maze.
         */
        ~Maze();

        /**
         * Getter for size_x.
         */
        index get_size_x();

        /**
         * Getter for size_y.
         */
        index get_size_y();

        /**
         * Creates and returns a Cell given the indexes of that cell. Cell is
         * invalidated when maze is destructured.
         */
        Cell<type> cell(index pos_x, index pos_y);

    protected:
        /**
         * The raw cells that make up the maze. Stored continuously in memory.
         * This is deallocated at the point of maze destruction.
         */
        RawCell<type>* cells;

        /**
         * The size of the mazes x dimension.
         */
        index size_x;

        /**
         * The size of the mazes y dimension.
         */
        index size_y;
    };
}

#endif
