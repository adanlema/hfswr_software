module code_generator (
    input wire clk,
    input wire rst,
    input wire sinc,         
    input wire [15:0] codigo,
    output wire out   
);

reg out_data = 0;
reg [7:0] bit_counter = 0;
reg [11:0] counter = 0;  

always @(posedge clk or posedge rst) begin
    if(!rst) begin
        counter = 0;
        bit_counter = 0;
        out_data = 0;
    end else begin
        if(sinc) begin
            if (bit_counter < 16) begin 
                if (counter == 12'd1228) begin      // 122.88MHz / 1228.8 = 100kHz
                    counter = 0;
                    out_data = codigo[bit_counter];
                    bit_counter = bit_counter + 1; // Incremento el contador del bit.
                end else begin
                    counter = counter + 1;
                end
            end else
                out_data = 0;
        end else begin
            counter = 0;
            bit_counter = 0;
            out_data = 0; 
        end
    end
end

assign out = out_data;

endmodule
