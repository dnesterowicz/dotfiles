vim.o.number = true
vim.o.relativenumber = true
vim.o.undofile = true
vim.o.confirm = true 
vim.o.expandtab = true
vim.o.tabstop = 4
vim.o.shiftwidth = 0 -- set to 0 to default to tabstop value
vim.o.ignorecase = true
vim.o.smartcase = true
vim.o.wrap = false
vim.o.splitbelow = true
vim.o.signcolumn = "yes"
vim.o.clipboard = "unnamedplus"
vim.g.mapleader = " "


vim.pack.add({
	"https://github.com/stevearc/oil.nvim",
	"https://github.com/nvim-treesitter/nvim-treesitter",
    "https://github.com/nvim-lua/plenary.nvim", -- telescope dependency
	"https://github.com/nvim-telescope/telescope.nvim",
    "https://github.com/nvim-tree/nvim-web-devicons", -- optional
    "https://github.com/vague2k/vague.nvim",
})


require("oil").setup({
	columns = { "icon" },
})


vim.api.nvim_create_autocmd("FileType", {
	pattern = { "markdown", "lua", "python", "javascript", "c", "cpp" },
	callback = function()
		vim.treesitter.start()
	end,
})


local telescope = require("telescope")
telescope.setup({
	defaults = {
		preview = { treesitter = false },
		sorting_strategy = "ascending",
		path_displays = { "smart" },
		layout_config = {
			height = 100,
			width = 400,
			prompt_position = "top",
			preview_cutoff = 40,
		},
	},
})


require("vague").setup()
vim.cmd("colorscheme vague")


vim.keymap.set("n", "-", "<CMD>Oil<CR>", { desc = "Open parent directory" })

local builtin = require("telescope.builtin")
vim.keymap.set("n", "<leader>sf", builtin.find_files, { desc = "[S]earch [F]iles" })
vim.keymap.set("n", "<leader>sc", function() builtin.find_files({ cwd = "~/.config/" }) end, { desc = "[S]earch [F]iles" })
vim.keymap.set("n", "<leader>sg", builtin.live_grep, { desc = "[S]earch Files by [G]rep" })
vim.keymap.set("n", "<leader>sw", builtin.grep_string, { desc = "[S]earch current [W]ord" })
vim.keymap.set("n", "<leader><leader>", builtin.buffers, { desc = "[ ] Find existing buffers" })
vim.keymap.set("n", "<leader>sh", builtin.help_tags, { desc = "[S]earch [H]elp" })

vim.keymap.set("n", "<leader>/", function()
    builtin.current_buffer_fuzzy_find(require("telescope.themes").get_dropdown({
    winblend = 10,
    previewer = false,
    }))
end, { desc = "[/] Fuzzily search in current buffer" })

vim.keymap.set("n", "<leader>s/", function()
    builtin.live_grep({
    grep_open_files = true,
    prompt_title = "Live Grep in Open Files",
    })
end, { desc = "[S]earch [/] in Open Files" })

