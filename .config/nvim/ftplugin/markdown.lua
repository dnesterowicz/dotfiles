-- Add the key mappings only for Markdown files in a zk notebook.
if require("zk.util").notebook_root(vim.fn.expand("%:p")) ~= nil then
    local function map(...)
        vim.api.nvim_buf_set_keymap(0, ...)
    end

    -- Open the link under the cursor
    map("n", "<CR>", "<Cmd>lua vim.lsp.buf.definition()<CR>", { noremap = true, silent = false })
end
